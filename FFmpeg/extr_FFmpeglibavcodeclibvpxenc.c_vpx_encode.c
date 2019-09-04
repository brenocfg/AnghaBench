#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vpx_enc_frame_flags_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct vpx_image {unsigned int* stride; int /*<<< orphan*/ ** planes; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  sz; int /*<<< orphan*/  buf; } ;
struct TYPE_13__ {TYPE_1__ twopass_stats; int /*<<< orphan*/  deadline; int /*<<< orphan*/  encoder_alpha; scalar_t__ is_alpha; int /*<<< orphan*/  encoder; struct vpx_image rawimg_alpha; struct vpx_image rawimg; } ;
typedef  TYPE_2__ VPxContext ;
struct TYPE_16__ {scalar_t__ codec_id; int flags; void* stats_out; int /*<<< orphan*/  ticks_per_frame; TYPE_2__* priv_data; } ;
struct TYPE_15__ {int /*<<< orphan*/  value; } ;
struct TYPE_14__ {unsigned int* linesize; unsigned int height; scalar_t__ pict_type; scalar_t__ metadata; int /*<<< orphan*/  pts; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 unsigned int AV_BASE64_SIZE (int /*<<< orphan*/ ) ; 
 int AV_CODEC_FLAG_PASS1 ; 
 scalar_t__ AV_CODEC_ID_VP8 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ CONFIG_LIBVPX_VP8_ENCODER ; 
 int /*<<< orphan*/  ENOMEM ; 
 int VPX_CODEC_OK ; 
 int /*<<< orphan*/  VPX_EFLAG_FORCE_KF ; 
 size_t VPX_PLANE_U ; 
 size_t VPX_PLANE_V ; 
 size_t VPX_PLANE_Y ; 
 int /*<<< orphan*/  av_base64_encode (void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_dict_get (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 void* av_malloc (unsigned int) ; 
 int /*<<< orphan*/  log_encoder_error (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int queue_frames (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int vpx_codec_encode (int /*<<< orphan*/ *,struct vpx_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpx_encode(AVCodecContext *avctx, AVPacket *pkt,
                      const AVFrame *frame, int *got_packet)
{
    VPxContext *ctx = avctx->priv_data;
    struct vpx_image *rawimg = NULL;
    struct vpx_image *rawimg_alpha = NULL;
    int64_t timestamp = 0;
    int res, coded_size;
    vpx_enc_frame_flags_t flags = 0;

    if (frame) {
        rawimg                      = &ctx->rawimg;
        rawimg->planes[VPX_PLANE_Y] = frame->data[0];
        rawimg->planes[VPX_PLANE_U] = frame->data[1];
        rawimg->planes[VPX_PLANE_V] = frame->data[2];
        rawimg->stride[VPX_PLANE_Y] = frame->linesize[0];
        rawimg->stride[VPX_PLANE_U] = frame->linesize[1];
        rawimg->stride[VPX_PLANE_V] = frame->linesize[2];
        if (ctx->is_alpha) {
            uint8_t *u_plane, *v_plane;
            rawimg_alpha = &ctx->rawimg_alpha;
            rawimg_alpha->planes[VPX_PLANE_Y] = frame->data[3];
            u_plane = av_malloc(frame->linesize[1] * frame->height);
            v_plane = av_malloc(frame->linesize[2] * frame->height);
            if (!u_plane || !v_plane) {
                av_free(u_plane);
                av_free(v_plane);
                return AVERROR(ENOMEM);
            }
            memset(u_plane, 0x80, frame->linesize[1] * frame->height);
            rawimg_alpha->planes[VPX_PLANE_U] = u_plane;
            memset(v_plane, 0x80, frame->linesize[2] * frame->height);
            rawimg_alpha->planes[VPX_PLANE_V] = v_plane;
            rawimg_alpha->stride[VPX_PLANE_Y] = frame->linesize[0];
            rawimg_alpha->stride[VPX_PLANE_U] = frame->linesize[1];
            rawimg_alpha->stride[VPX_PLANE_V] = frame->linesize[2];
        }
        timestamp                   = frame->pts;
#if VPX_IMAGE_ABI_VERSION >= 4
        switch (frame->color_range) {
        case AVCOL_RANGE_MPEG:
            rawimg->range = VPX_CR_STUDIO_RANGE;
            break;
        case AVCOL_RANGE_JPEG:
            rawimg->range = VPX_CR_FULL_RANGE;
            break;
        }
#endif
        if (frame->pict_type == AV_PICTURE_TYPE_I)
            flags |= VPX_EFLAG_FORCE_KF;
        if (CONFIG_LIBVPX_VP8_ENCODER && avctx->codec_id == AV_CODEC_ID_VP8 && frame->metadata) {
            AVDictionaryEntry* en = av_dict_get(frame->metadata, "vp8-flags", NULL, 0);
            if (en) {
                flags |= strtoul(en->value, NULL, 10);
            }
        }
    }

    res = vpx_codec_encode(&ctx->encoder, rawimg, timestamp,
                           avctx->ticks_per_frame, flags, ctx->deadline);
    if (res != VPX_CODEC_OK) {
        log_encoder_error(avctx, "Error encoding frame");
        return AVERROR_INVALIDDATA;
    }

    if (ctx->is_alpha) {
        res = vpx_codec_encode(&ctx->encoder_alpha, rawimg_alpha, timestamp,
                               avctx->ticks_per_frame, flags, ctx->deadline);
        if (res != VPX_CODEC_OK) {
            log_encoder_error(avctx, "Error encoding alpha frame");
            return AVERROR_INVALIDDATA;
        }
    }

    coded_size = queue_frames(avctx, pkt);

    if (!frame && avctx->flags & AV_CODEC_FLAG_PASS1) {
        unsigned int b64_size = AV_BASE64_SIZE(ctx->twopass_stats.sz);

        avctx->stats_out = av_malloc(b64_size);
        if (!avctx->stats_out) {
            av_log(avctx, AV_LOG_ERROR, "Stat buffer alloc (%d bytes) failed\n",
                   b64_size);
            return AVERROR(ENOMEM);
        }
        av_base64_encode(avctx->stats_out, b64_size, ctx->twopass_stats.buf,
                         ctx->twopass_stats.sz);
    }

    if (rawimg_alpha) {
        av_freep(&rawimg_alpha->planes[VPX_PLANE_U]);
        av_freep(&rawimg_alpha->planes[VPX_PLANE_V]);
    }

    *got_packet = !!coded_size;
    return 0;
}