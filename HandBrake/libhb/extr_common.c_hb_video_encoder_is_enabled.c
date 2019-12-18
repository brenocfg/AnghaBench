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
typedef  int /*<<< orphan*/  x265_api ;
typedef  int /*<<< orphan*/  x264_api_t ;

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_MPEG2 144 
#define  HB_VCODEC_FFMPEG_MPEG4 143 
#define  HB_VCODEC_FFMPEG_NVENC_H264 142 
#define  HB_VCODEC_FFMPEG_NVENC_H265 141 
#define  HB_VCODEC_FFMPEG_VCE_H264 140 
#define  HB_VCODEC_FFMPEG_VCE_H265 139 
#define  HB_VCODEC_FFMPEG_VP8 138 
#define  HB_VCODEC_FFMPEG_VP9 137 
#define  HB_VCODEC_FFMPEG_VT_H264 136 
#define  HB_VCODEC_FFMPEG_VT_H265 135 
 int HB_VCODEC_QSV_MASK ; 
#define  HB_VCODEC_THEORA 134 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 int /*<<< orphan*/  X265_BUILD ; 
 int hb_nvenc_h264_available () ; 
 int hb_nvenc_h265_available () ; 
 int hb_qsv_video_encoder_is_enabled (int) ; 
 int hb_vce_h264_available () ; 
 int hb_vce_h265_available () ; 
 int /*<<< orphan*/  hb_video_encoder_get_depth (int) ; 
 int hb_vt_h264_is_available () ; 
 int hb_vt_h265_is_available () ; 
 int /*<<< orphan*/ * hb_x264_api_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x265_api_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hb_video_encoder_is_enabled(int encoder, int disable_hardware)
{
    // Hardware Encoders
    if (!disable_hardware)
    {
#if HB_PROJECT_FEATURE_QSV
        if (encoder & HB_VCODEC_QSV_MASK)
        {
            return hb_qsv_video_encoder_is_enabled(encoder);
        }
#endif

        switch (encoder){
#if HB_PROJECT_FEATURE_VCE
            case HB_VCODEC_FFMPEG_VCE_H264:
               return hb_vce_h264_available();
            case HB_VCODEC_FFMPEG_VCE_H265:
                return hb_vce_h265_available();
#endif

#if HB_PROJECT_FEATURE_NVENC
            case HB_VCODEC_FFMPEG_NVENC_H264:
                return hb_nvenc_h264_available();
            case HB_VCODEC_FFMPEG_NVENC_H265:
                return hb_nvenc_h265_available();
#endif

#ifdef __APPLE__
            case HB_VCODEC_FFMPEG_VT_H264:
                return hb_vt_h264_is_available();
            case HB_VCODEC_FFMPEG_VT_H265:
                return hb_vt_h265_is_available();
#endif
        }
    }

    // Software Encoders
    switch (encoder)
    {
        // the following encoders are always enabled
        case HB_VCODEC_THEORA:
        case HB_VCODEC_FFMPEG_MPEG4:
        case HB_VCODEC_FFMPEG_MPEG2:
        case HB_VCODEC_FFMPEG_VP8:
        case HB_VCODEC_FFMPEG_VP9:
            return 1;

#if HB_PROJECT_FEATURE_X265
        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_X265_10BIT:
        case HB_VCODEC_X265_12BIT:
        case HB_VCODEC_X265_16BIT:
        {
            const x265_api *api;
            api = x265_api_query(hb_video_encoder_get_depth(encoder), X265_BUILD, NULL);
            return (api != NULL);
        };
#endif

        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X264_10BIT:
        {
            const x264_api_t *api;
            api = hb_x264_api_get(hb_video_encoder_get_depth(encoder));
            return (api != NULL);
        }

        default:
            return 0;
    }
}