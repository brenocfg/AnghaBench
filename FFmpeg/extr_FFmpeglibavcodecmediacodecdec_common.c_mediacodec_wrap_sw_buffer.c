#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_27__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_30__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_33__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_27__ pkt_timebase; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_32__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_31__ {int /*<<< orphan*/  presentationTimeUs; } ;
struct TYPE_29__ {int color_format; int /*<<< orphan*/  codec; int /*<<< orphan*/  codec_name; int /*<<< orphan*/  crop_right; int /*<<< orphan*/  crop_left; int /*<<< orphan*/  crop_bottom; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  slice_height; int /*<<< orphan*/  stride; } ;
typedef  TYPE_1__ MediaCodecDecContext ;
typedef  TYPE_2__ FFAMediaCodecBufferInfo ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
#define  COLOR_FormatYUV420Planar 134 
#define  COLOR_FormatYUV420SemiPlanar 133 
#define  COLOR_QCOM_FormatYUV420PackedSemiPlanar64x32Tile2m8ka 132 
#define  COLOR_QCOM_FormatYUV420SemiPlanar 131 
#define  COLOR_QCOM_FormatYUV420SemiPlanar32m 130 
#define  COLOR_TI_FormatYUV420PackedSemiPlanar 129 
#define  COLOR_TI_FormatYUV420PackedSemiPlanarInterlaced 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_27__) ; 
 int ff_AMediaCodec_releaseOutputBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mediacodec_sw_buffer_copy_yuv420_packed_semi_planar (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_mediacodec_sw_buffer_copy_yuv420_packed_semi_planar_64x32Tile2m8ka (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_mediacodec_sw_buffer_copy_yuv420_planar (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_mediacodec_sw_buffer_copy_yuv420_semi_planar (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int mediacodec_wrap_sw_buffer(AVCodecContext *avctx,
                                  MediaCodecDecContext *s,
                                  uint8_t *data,
                                  size_t size,
                                  ssize_t index,
                                  FFAMediaCodecBufferInfo *info,
                                  AVFrame *frame)
{
    int ret = 0;
    int status = 0;

    frame->width = avctx->width;
    frame->height = avctx->height;
    frame->format = avctx->pix_fmt;

    /* MediaCodec buffers needs to be copied to our own refcounted buffers
     * because the flush command invalidates all input and output buffers.
     */
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Could not allocate buffer\n");
        goto done;
    }

    /* Override frame->pkt_pts as ff_get_buffer will override its value based
     * on the last avpacket received which is not in sync with the frame:
     *   * N avpackets can be pushed before 1 frame is actually returned
     *   * 0-sized avpackets are pushed to flush remaining frames at EOS */
    if (avctx->pkt_timebase.num && avctx->pkt_timebase.den) {
        frame->pts = av_rescale_q(info->presentationTimeUs,
                                      AV_TIME_BASE_Q,
                                      avctx->pkt_timebase);
    } else {
        frame->pts = info->presentationTimeUs;
    }
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
    frame->pkt_pts = frame->pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    frame->pkt_dts = AV_NOPTS_VALUE;

    av_log(avctx, AV_LOG_TRACE,
            "Frame: width=%d stride=%d height=%d slice-height=%d "
            "crop-top=%d crop-bottom=%d crop-left=%d crop-right=%d encoder=%s "
            "destination linesizes=%d,%d,%d\n" ,
            avctx->width, s->stride, avctx->height, s->slice_height,
            s->crop_top, s->crop_bottom, s->crop_left, s->crop_right, s->codec_name,
            frame->linesize[0], frame->linesize[1], frame->linesize[2]);

    switch (s->color_format) {
    case COLOR_FormatYUV420Planar:
        ff_mediacodec_sw_buffer_copy_yuv420_planar(avctx, s, data, size, info, frame);
        break;
    case COLOR_FormatYUV420SemiPlanar:
    case COLOR_QCOM_FormatYUV420SemiPlanar:
    case COLOR_QCOM_FormatYUV420SemiPlanar32m:
        ff_mediacodec_sw_buffer_copy_yuv420_semi_planar(avctx, s, data, size, info, frame);
        break;
    case COLOR_TI_FormatYUV420PackedSemiPlanar:
    case COLOR_TI_FormatYUV420PackedSemiPlanarInterlaced:
        ff_mediacodec_sw_buffer_copy_yuv420_packed_semi_planar(avctx, s, data, size, info, frame);
        break;
    case COLOR_QCOM_FormatYUV420PackedSemiPlanar64x32Tile2m8ka:
        ff_mediacodec_sw_buffer_copy_yuv420_packed_semi_planar_64x32Tile2m8ka(avctx, s, data, size, info, frame);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unsupported color format 0x%x (value=%d)\n",
            s->color_format, s->color_format);
        ret = AVERROR(EINVAL);
        goto done;
    }

    ret = 0;
done:
    status = ff_AMediaCodec_releaseOutputBuffer(s->codec, index, 0);
    if (status < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to release output buffer\n");
        ret = AVERROR_EXTERNAL;
    }

    return ret;
}