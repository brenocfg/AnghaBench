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

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_NVENC_H264 135 
#define  HB_VCODEC_FFMPEG_NVENC_H265 134 
#define  HB_VCODEC_FFMPEG_VCE_H264 133 
#define  HB_VCODEC_FFMPEG_VCE_H265 132 
#define  HB_VCODEC_FFMPEG_VP8 131 
#define  HB_VCODEC_FFMPEG_VP9 130 
#define  HB_VCODEC_FFMPEG_VT_H264 129 
#define  HB_VCODEC_FFMPEG_VT_H265 128 
 char const* const* h26x_nvenc_preset_names ; 
 char const* const* h26x_vt_preset_name ; 
 char const* const* hb_vce_preset_names ; 
 char const* const* vpx_preset_names ; 

const char* const* hb_av_preset_get_names(int encoder)
{
    switch (encoder)
    {
        case HB_VCODEC_FFMPEG_VP8:
        case HB_VCODEC_FFMPEG_VP9:
            return vpx_preset_names;

        case HB_VCODEC_FFMPEG_VCE_H264:
        case HB_VCODEC_FFMPEG_VCE_H265:
            return hb_vce_preset_names;

        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_NVENC_H265:
            return h26x_nvenc_preset_names;

        case HB_VCODEC_FFMPEG_VT_H264:
        case HB_VCODEC_FFMPEG_VT_H265:
            return h26x_vt_preset_name;

        default:
            return NULL;
    }
}