#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ frame_ct_out; int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_18__ {int width; int height; scalar_t__ pix_fmt; scalar_t__ extradata_size; scalar_t__ extradata; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; TYPE_1__* priv_data; } ;
struct TYPE_17__ {int* linesize; scalar_t__ format; int width; int height; scalar_t__ pts; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; scalar_t__* data; TYPE_14__** buf; } ;
struct TYPE_15__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  CMVideoCodecType ;
typedef  int /*<<< orphan*/ * CMSampleBufferRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int VTCompressionSessionCompleteFrames (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_14__* av_buffer_alloc (int) ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kCMTimeIndefinite ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int vtenc_create_encoder (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int vtenc_q_pop (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int vtenc_send_frame (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int vtenc_populate_extradata(AVCodecContext   *avctx,
                                    CMVideoCodecType codec_type,
                                    CFStringRef      profile_level,
                                    CFNumberRef      gamma_level,
                                    CFDictionaryRef  enc_info,
                                    CFDictionaryRef  pixel_buffer_info)
{
    VTEncContext *vtctx = avctx->priv_data;
    AVFrame *frame = av_frame_alloc();
    int y_size = avctx->width * avctx->height;
    int chroma_size = (avctx->width / 2) * (avctx->height / 2);
    CMSampleBufferRef buf = NULL;
    int status;

    if (!frame)
        return AVERROR(ENOMEM);

    frame->buf[0] = av_buffer_alloc(y_size + 2 * chroma_size);

    if(!frame->buf[0]){
        status = AVERROR(ENOMEM);
        goto pe_cleanup;
    }

    status = vtenc_create_encoder(avctx,
                                  codec_type,
                                  profile_level,
                                  gamma_level,
                                  enc_info,
                                  pixel_buffer_info,
                                  &vtctx->session);
    if (status)
        goto pe_cleanup;

    frame->data[0] = frame->buf[0]->data;
    memset(frame->data[0],   0,      y_size);

    frame->data[1] = frame->buf[0]->data + y_size;
    memset(frame->data[1], 128, chroma_size);


    if (avctx->pix_fmt == AV_PIX_FMT_YUV420P) {
        frame->data[2] = frame->buf[0]->data + y_size + chroma_size;
        memset(frame->data[2], 128, chroma_size);
    }

    frame->linesize[0] = avctx->width;

    if (avctx->pix_fmt == AV_PIX_FMT_YUV420P) {
        frame->linesize[1] =
        frame->linesize[2] = (avctx->width + 1) / 2;
    } else {
        frame->linesize[1] = (avctx->width + 1) / 2;
    }

    frame->format          = avctx->pix_fmt;
    frame->width           = avctx->width;
    frame->height          = avctx->height;
    frame->colorspace      = avctx->colorspace;
    frame->color_range     = avctx->color_range;
    frame->color_trc       = avctx->color_trc;
    frame->color_primaries = avctx->color_primaries;

    frame->pts = 0;
    status = vtenc_send_frame(avctx, vtctx, frame);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error sending frame: %d\n", status);
        goto pe_cleanup;
    }

    //Populates extradata - output frames are flushed and param sets are available.
    status = VTCompressionSessionCompleteFrames(vtctx->session,
                                                kCMTimeIndefinite);

    if (status)
        goto pe_cleanup;

    status = vtenc_q_pop(vtctx, 0, &buf, NULL);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "popping: %d\n", status);
        goto pe_cleanup;
    }

    CFRelease(buf);



pe_cleanup:
    if(vtctx->session)
        CFRelease(vtctx->session);

    vtctx->session = NULL;
    vtctx->frame_ct_out = 0;

    av_frame_unref(frame);
    av_frame_free(&frame);

    av_assert0(status != 0 || (avctx->extradata && avctx->extradata_size > 0));

    return status;
}