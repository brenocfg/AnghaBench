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
#define  HB_VCODEC_FFMPEG_NVENC_H264 131 
#define  HB_VCODEC_FFMPEG_NVENC_H265 130 
#define  HB_VCODEC_FFMPEG_VT_H264 129 
#define  HB_VCODEC_FFMPEG_VT_H265 128 
 char const* const* h264_nvenc_profile_names ; 
 char const* const* h264_vt_profile_name ; 
 char const* const* h265_nvenc_profile_names ; 
 char const* const* h265_vt_profile_name ; 

const char* const* hb_av_profile_get_names(int encoder)
{
    switch (encoder)
    {
        case HB_VCODEC_FFMPEG_NVENC_H264:
            return h264_nvenc_profile_names;
        case HB_VCODEC_FFMPEG_NVENC_H265:
            return h265_nvenc_profile_names;
        case HB_VCODEC_FFMPEG_VT_H264:
            return h264_vt_profile_name;
        case HB_VCODEC_FFMPEG_VT_H265:
            return h265_vt_profile_name;

         default:
             return NULL;
     }
}