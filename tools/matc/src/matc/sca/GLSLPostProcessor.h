/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_GLSLPOSTPROCESSOR_H
#define TNT_GLSLPOSTPROCESSOR_H

#include <string>
#include <vector>

#include <filament/driver/DriverEnums.h>

#include <matc/Config.h>

#include <ShaderLang.h>

#include <spirv-tools/optimizer.hpp>

namespace matc {

class GLSLPostProcessor {
public:
    GLSLPostProcessor(const Config& config);

    ~GLSLPostProcessor();

    using SpirvBlob = std::vector<uint32_t>;

    bool process(const std::string& inputShader, filament::driver::ShaderType shaderType,
            filament::driver::ShaderModel shaderModel, std::string* outputGlsl,
            SpirvBlob* outputSpirv);

private:
    void fullOptimization(const glslang::TShader& tShader,
            const filament::driver::ShaderModel shaderModel) const;
    void preprocessOptimization(glslang::TShader& tShader,
            const filament::driver::ShaderModel shaderModel) const;

    void registerSizePasses(spvtools::Optimizer& optimizer) const;
    void registerPerformancePasses(spvtools::Optimizer& optimizer) const;

    const Config& mConfig;
    std::string* mGlslOutput = nullptr;
    SpirvBlob* mSpirvOutput = nullptr;
    EShLanguage mShLang = EShLangFragment;
    int mLangVersion = 0;
};

} // namespace matc

#endif //TNT_GLSLPOSTPROCESSOR_H
