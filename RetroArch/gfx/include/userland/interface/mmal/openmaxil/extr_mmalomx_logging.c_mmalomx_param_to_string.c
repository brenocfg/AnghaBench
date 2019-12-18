#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ OMX_INDEXTYPE ;

/* Variables and functions */
#define  OMX_IndexAutoPauseAfterCapture 164 
#define  OMX_IndexConfigCapturing 163 
#define  OMX_IndexConfigCommonDigitalZoom 162 
#define  OMX_IndexConfigCommonExposureValue 161 
#define  OMX_IndexConfigCommonInputCrop 160 
#define  OMX_IndexConfigCommonMirror 159 
#define  OMX_IndexConfigCommonOutputCrop 158 
#define  OMX_IndexConfigCommonRotate 157 
#define  OMX_IndexConfigCommonScale 156 
#define  OMX_IndexConfigCommonWhiteBalance 155 
#define  OMX_IndexParamActiveStream 154 
#define  OMX_IndexParamAudioAac 153 
#define  OMX_IndexParamAudioInit 152 
#define  OMX_IndexParamAudioMp3 151 
#define  OMX_IndexParamAudioPcm 150 
#define  OMX_IndexParamAudioPortFormat 149 
#define  OMX_IndexParamCommonSensorMode 148 
#define  OMX_IndexParamCompBufferSupplier 147 
#define  OMX_IndexParamContentURI 146 
#define  OMX_IndexParamImageInit 145 
#define  OMX_IndexParamImagePortFormat 144 
#define  OMX_IndexParamNumAvailableStreams 143 
#define  OMX_IndexParamOtherInit 142 
#define  OMX_IndexParamOtherPortFormat 141 
#define  OMX_IndexParamPortDefinition 140 
#define  OMX_IndexParamPriorityMgmt 139 
#define  OMX_IndexParamStandardComponentRole 138 
#define  OMX_IndexParamVideoAvc 137 
#define  OMX_IndexParamVideoBitrate 136 
#define  OMX_IndexParamVideoH263 135 
#define  OMX_IndexParamVideoInit 134 
#define  OMX_IndexParamVideoMpeg2 133 
#define  OMX_IndexParamVideoMpeg4 132 
#define  OMX_IndexParamVideoPortFormat 131 
#define  OMX_IndexParamVideoProfileLevelQuerySupported 130 
#define  OMX_IndexParamVideoRv 129 
#define  OMX_IndexParamVideoWmv 128 
 char* mmalomx_parameter_name_omx (int /*<<< orphan*/ ) ; 

const char *mmalomx_param_to_string(OMX_INDEXTYPE param)
{
  static const struct {
    const char *string;
    const OMX_INDEXTYPE param;
  } param_to_names[] =
  {
    {"OMX_IndexParamPriorityMgmt", OMX_IndexParamPriorityMgmt},
    {"OMX_IndexParamAudioInit", OMX_IndexParamAudioInit},
    {"OMX_IndexParamImageInit", OMX_IndexParamImageInit},
    {"OMX_IndexParamVideoInit", OMX_IndexParamVideoInit},
    {"OMX_IndexParamOtherInit", OMX_IndexParamOtherInit},
    {"OMX_IndexParamPortDefinition", OMX_IndexParamPortDefinition},
    {"OMX_IndexParamCompBufferSupplier", OMX_IndexParamCompBufferSupplier},
    {"OMX_IndexParamAudioPortFormat", OMX_IndexParamAudioPortFormat},
    {"OMX_IndexParamVideoPortFormat", OMX_IndexParamVideoPortFormat},
    {"OMX_IndexParamImagePortFormat", OMX_IndexParamImagePortFormat},
    {"OMX_IndexParamOtherPortFormat", OMX_IndexParamOtherPortFormat},
    {"OMX_IndexParamAudioPcm", OMX_IndexParamAudioPcm},
    {"OMX_IndexParamAudioAac", OMX_IndexParamAudioAac},
    {"OMX_IndexParamAudioMp3", OMX_IndexParamAudioMp3},
    {"OMX_IndexParamVideoMpeg2", OMX_IndexParamVideoMpeg2},
    {"OMX_IndexParamVideoMpeg4", OMX_IndexParamVideoMpeg4},
    {"OMX_IndexParamVideoWmv", OMX_IndexParamVideoWmv},
    {"OMX_IndexParamVideoRv", OMX_IndexParamVideoRv},
    {"OMX_IndexParamVideoAvc", OMX_IndexParamVideoAvc},
    {"OMX_IndexParamVideoH263", OMX_IndexParamVideoH263},
    {"OMX_IndexParamStandardComponentRole", OMX_IndexParamStandardComponentRole},
    {"OMX_IndexParamContentURI", OMX_IndexParamContentURI},
    {"OMX_IndexParamCommonSensorMode", OMX_IndexParamCommonSensorMode},
    {"OMX_IndexConfigCommonWhiteBalance", OMX_IndexConfigCommonWhiteBalance},
    {"OMX_IndexConfigCommonDigitalZoom", OMX_IndexConfigCommonDigitalZoom},
    {"OMX_IndexConfigCommonExposureValue", OMX_IndexConfigCommonExposureValue},
    {"OMX_IndexConfigCapturing", OMX_IndexConfigCapturing},
    {"OMX_IndexAutoPauseAfterCapture", OMX_IndexAutoPauseAfterCapture},
    {"OMX_IndexConfigCommonRotate", OMX_IndexConfigCommonRotate},
    {"OMX_IndexConfigCommonMirror", OMX_IndexConfigCommonMirror},
    {"OMX_IndexConfigCommonScale", OMX_IndexConfigCommonScale},
    {"OMX_IndexConfigCommonInputCrop", OMX_IndexConfigCommonInputCrop},
    {"OMX_IndexConfigCommonOutputCrop", OMX_IndexConfigCommonOutputCrop},
    {"OMX_IndexParamNumAvailableStreams", OMX_IndexParamNumAvailableStreams},
    {"OMX_IndexParamActiveStream", OMX_IndexParamActiveStream},
    {"OMX_IndexParamVideoBitrate", OMX_IndexParamVideoBitrate},
    {"OMX_IndexParamVideoProfileLevelQuerySupported", OMX_IndexParamVideoProfileLevelQuerySupported},

    {"OMX_IndexParam unknown", (OMX_INDEXTYPE)0}
  };
  const char *name = mmalomx_parameter_name_omx((uint32_t)param);
  int i;

  if (name)
     return name;

  for(i = 0; param_to_names[i].param &&
      param_to_names[i].param != param; i++);

  return param_to_names[i].string;
}