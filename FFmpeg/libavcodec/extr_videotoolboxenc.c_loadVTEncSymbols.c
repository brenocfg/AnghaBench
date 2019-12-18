#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ getParameterSetAtIndex ;
struct TYPE_2__ {scalar_t__ CMVideoFormatDescriptionGetHEVCParameterSetAtIndex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SYM (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 TYPE_1__ compat_keys ; 
 scalar_t__ dlsym (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kCVImageBufferColorPrimaries_ITU_R_2020 ; 
 int /*<<< orphan*/  kCVImageBufferTransferFunction_ITU_R_2020 ; 
 int /*<<< orphan*/  kCVImageBufferYCbCrMatrix_ITU_R_2020 ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_H264EntropyMode ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_RealTime ; 
 int /*<<< orphan*/  kVTH264EntropyMode_CABAC ; 
 int /*<<< orphan*/  kVTH264EntropyMode_CAVLC ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_4_0 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_4_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_5_0 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_5_1 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_5_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Extended_5_0 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Extended_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_3_0 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_3_1 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_3_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_4_0 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_4_1 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_4_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_5_1 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_5_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Main_4_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Main_5_1 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Main_5_2 ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Main_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_HEVC_Main10_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_HEVC_Main_AutoLevel ; 
 int /*<<< orphan*/  kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder ; 
 int /*<<< orphan*/  kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder ; 

__attribute__((used)) static void loadVTEncSymbols(){
    compat_keys.CMVideoFormatDescriptionGetHEVCParameterSetAtIndex =
        (getParameterSetAtIndex)dlsym(
            RTLD_DEFAULT,
            "CMVideoFormatDescriptionGetHEVCParameterSetAtIndex"
        );

    GET_SYM(kCVImageBufferColorPrimaries_ITU_R_2020,   "ITU_R_2020");
    GET_SYM(kCVImageBufferTransferFunction_ITU_R_2020, "ITU_R_2020");
    GET_SYM(kCVImageBufferYCbCrMatrix_ITU_R_2020,      "ITU_R_2020");

    GET_SYM(kVTCompressionPropertyKey_H264EntropyMode, "H264EntropyMode");
    GET_SYM(kVTH264EntropyMode_CAVLC, "CAVLC");
    GET_SYM(kVTH264EntropyMode_CABAC, "CABAC");

    GET_SYM(kVTProfileLevel_H264_Baseline_4_0,       "H264_Baseline_4_0");
    GET_SYM(kVTProfileLevel_H264_Baseline_4_2,       "H264_Baseline_4_2");
    GET_SYM(kVTProfileLevel_H264_Baseline_5_0,       "H264_Baseline_5_0");
    GET_SYM(kVTProfileLevel_H264_Baseline_5_1,       "H264_Baseline_5_1");
    GET_SYM(kVTProfileLevel_H264_Baseline_5_2,       "H264_Baseline_5_2");
    GET_SYM(kVTProfileLevel_H264_Baseline_AutoLevel, "H264_Baseline_AutoLevel");
    GET_SYM(kVTProfileLevel_H264_Main_4_2,           "H264_Main_4_2");
    GET_SYM(kVTProfileLevel_H264_Main_5_1,           "H264_Main_5_1");
    GET_SYM(kVTProfileLevel_H264_Main_5_2,           "H264_Main_5_2");
    GET_SYM(kVTProfileLevel_H264_Main_AutoLevel,     "H264_Main_AutoLevel");
    GET_SYM(kVTProfileLevel_H264_High_3_0,           "H264_High_3_0");
    GET_SYM(kVTProfileLevel_H264_High_3_1,           "H264_High_3_1");
    GET_SYM(kVTProfileLevel_H264_High_3_2,           "H264_High_3_2");
    GET_SYM(kVTProfileLevel_H264_High_4_0,           "H264_High_4_0");
    GET_SYM(kVTProfileLevel_H264_High_4_1,           "H264_High_4_1");
    GET_SYM(kVTProfileLevel_H264_High_4_2,           "H264_High_4_2");
    GET_SYM(kVTProfileLevel_H264_High_5_1,           "H264_High_5_1");
    GET_SYM(kVTProfileLevel_H264_High_5_2,           "H264_High_5_2");
    GET_SYM(kVTProfileLevel_H264_High_AutoLevel,     "H264_High_AutoLevel");
    GET_SYM(kVTProfileLevel_H264_Extended_5_0,       "H264_Extended_5_0");
    GET_SYM(kVTProfileLevel_H264_Extended_AutoLevel, "H264_Extended_AutoLevel");

    GET_SYM(kVTProfileLevel_HEVC_Main_AutoLevel,     "HEVC_Main_AutoLevel");
    GET_SYM(kVTProfileLevel_HEVC_Main10_AutoLevel,   "HEVC_Main10_AutoLevel");

    GET_SYM(kVTCompressionPropertyKey_RealTime, "RealTime");

    GET_SYM(kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder,
            "EnableHardwareAcceleratedVideoEncoder");
    GET_SYM(kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder,
            "RequireHardwareAcceleratedVideoEncoder");
}