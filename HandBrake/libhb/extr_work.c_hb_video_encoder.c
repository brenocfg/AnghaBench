#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* codec_param; } ;
typedef  TYPE_1__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 void* AV_CODEC_ID_H264 ; 
 void* AV_CODEC_ID_HEVC ; 
 void* AV_CODEC_ID_MPEG2VIDEO ; 
 void* AV_CODEC_ID_MPEG4 ; 
 void* AV_CODEC_ID_VP8 ; 
 void* AV_CODEC_ID_VP9 ; 
#define  HB_VCODEC_FFMPEG_MPEG2 147 
#define  HB_VCODEC_FFMPEG_MPEG4 146 
#define  HB_VCODEC_FFMPEG_NVENC_H264 145 
#define  HB_VCODEC_FFMPEG_NVENC_H265 144 
#define  HB_VCODEC_FFMPEG_VCE_H264 143 
#define  HB_VCODEC_FFMPEG_VCE_H265 142 
#define  HB_VCODEC_FFMPEG_VP8 141 
#define  HB_VCODEC_FFMPEG_VP9 140 
#define  HB_VCODEC_FFMPEG_VT_H264 139 
#define  HB_VCODEC_FFMPEG_VT_H265 138 
#define  HB_VCODEC_QSV_H264 137 
#define  HB_VCODEC_QSV_H265 136 
#define  HB_VCODEC_QSV_H265_10BIT 135 
#define  HB_VCODEC_THEORA 134 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 int /*<<< orphan*/  WORK_ENCAVCODEC ; 
 int /*<<< orphan*/  WORK_ENCQSV ; 
 int /*<<< orphan*/  WORK_ENCTHEORA ; 
 int /*<<< orphan*/  WORK_ENCX264 ; 
 int /*<<< orphan*/  WORK_ENCX265 ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 TYPE_1__* hb_get_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

hb_work_object_t* hb_video_encoder(hb_handle_t *h, int vcodec)
{
    hb_work_object_t * w = NULL;

    switch (vcodec)
    {
        case HB_VCODEC_FFMPEG_MPEG4:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_MPEG4;
            break;
        case HB_VCODEC_FFMPEG_MPEG2:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_MPEG2VIDEO;
            break;
        case HB_VCODEC_FFMPEG_VP8:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_VP8;
            break;
        case HB_VCODEC_FFMPEG_VP9:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_VP9;
            break;
        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X264_10BIT:
            w = hb_get_work(h, WORK_ENCX264);
            break;
        case HB_VCODEC_QSV_H264:
        case HB_VCODEC_QSV_H265:
        case HB_VCODEC_QSV_H265_10BIT:
            w = hb_get_work(h, WORK_ENCQSV);
            break;
        case HB_VCODEC_THEORA:
            w = hb_get_work(h, WORK_ENCTHEORA);
            break;
#if HB_PROJECT_FEATURE_X265
        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_X265_10BIT:
        case HB_VCODEC_X265_12BIT:
        case HB_VCODEC_X265_16BIT:
            w = hb_get_work(h, WORK_ENCX265);
            break;
#endif
#if HB_PROJECT_FEATURE_VCE
        case HB_VCODEC_FFMPEG_VCE_H264:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_H264;
            break;
        case HB_VCODEC_FFMPEG_VCE_H265:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_HEVC;
            break;
#endif
#if HB_PROJECT_FEATURE_NVENC
        case HB_VCODEC_FFMPEG_NVENC_H264:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_H264;
            break;
        case HB_VCODEC_FFMPEG_NVENC_H265:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_HEVC;
            break;
#endif
#ifdef __APPLE__
        case HB_VCODEC_FFMPEG_VT_H264:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_H264;
            break;
        case HB_VCODEC_FFMPEG_VT_H265:
            w = hb_get_work(h, WORK_ENCAVCODEC);
            w->codec_param = AV_CODEC_ID_HEVC;
            break;
#endif

        default:
            hb_error("Unknown video codec (0x%x)", vcodec );
    }

    return w;
}