#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_26__ {int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ kvz_picture ;
struct TYPE_27__ {scalar_t__ nal_unit_type; } ;
typedef  TYPE_4__ kvz_frame_info ;
struct TYPE_28__ {scalar_t__ len; int /*<<< orphan*/  data; struct TYPE_28__* next; } ;
typedef  TYPE_5__ kvz_data_chunk ;
struct TYPE_32__ {scalar_t__ pix_fmt; TYPE_6__* priv_data; } ;
struct TYPE_31__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; int /*<<< orphan*/  pts; int /*<<< orphan*/  linesize; scalar_t__ data; } ;
struct TYPE_30__ {scalar_t__ data; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
struct TYPE_29__ {TYPE_2__* api; int /*<<< orphan*/  encoder; TYPE_1__* config; } ;
struct TYPE_25__ {int (* encoder_encode ) (int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__**,scalar_t__*,TYPE_3__**,int /*<<< orphan*/ *,TYPE_4__*) ;int /*<<< orphan*/  (* chunk_free ) (TYPE_5__*) ;int /*<<< orphan*/  (* picture_free ) (TYPE_3__*) ;TYPE_3__* (* picture_alloc ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_24__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_6__ LibkvazaarContext ;
typedef  TYPE_7__ AVPacket ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ KVZ_NAL_BLA_W_LP ; 
 scalar_t__ KVZ_NAL_RSV_IRAP_VCL23 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (scalar_t__) ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_alloc_packet2 (TYPE_9__*,TYPE_7__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* stub1 (scalar_t__,scalar_t__) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__**,scalar_t__*,TYPE_3__**,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*) ; 

__attribute__((used)) static int libkvazaar_encode(AVCodecContext *avctx,
                             AVPacket *avpkt,
                             const AVFrame *frame,
                             int *got_packet_ptr)
{
    LibkvazaarContext *ctx = avctx->priv_data;
    kvz_picture *input_pic = NULL;
    kvz_picture *recon_pic = NULL;
    kvz_frame_info frame_info;
    kvz_data_chunk *data_out = NULL;
    uint32_t len_out = 0;
    int retval = 0;

    *got_packet_ptr = 0;

    if (frame) {
        if (frame->width != ctx->config->width ||
            frame->height != ctx->config->height) {
            av_log(avctx, AV_LOG_ERROR,
                   "Changing video dimensions during encoding is not supported. "
                   "(changed from %dx%d to %dx%d)\n",
                   ctx->config->width, ctx->config->height,
                   frame->width, frame->height);
            retval = AVERROR_INVALIDDATA;
            goto done;
        }

        if (frame->format != avctx->pix_fmt) {
            av_log(avctx, AV_LOG_ERROR,
                   "Changing pixel format during encoding is not supported. "
                   "(changed from %s to %s)\n",
                   av_get_pix_fmt_name(avctx->pix_fmt),
                   av_get_pix_fmt_name(frame->format));
            retval = AVERROR_INVALIDDATA;
            goto done;
        }

        // Allocate input picture for kvazaar.
        input_pic = ctx->api->picture_alloc(frame->width, frame->height);
        if (!input_pic) {
            av_log(avctx, AV_LOG_ERROR, "Failed to allocate picture.\n");
            retval = AVERROR(ENOMEM);
            goto done;
        }

        // Copy pixels from frame to input_pic.
        {
            int dst_linesizes[4] = {
              frame->width,
              frame->width / 2,
              frame->width / 2,
              0
            };
            av_image_copy(input_pic->data, dst_linesizes,
                          (const uint8_t **)frame->data, frame->linesize,
                          frame->format, frame->width, frame->height);
        }

        input_pic->pts = frame->pts;
    }

    retval = ctx->api->encoder_encode(ctx->encoder,
                                      input_pic,
                                      &data_out, &len_out,
                                      &recon_pic, NULL,
                                      &frame_info);
    if (!retval) {
        av_log(avctx, AV_LOG_ERROR, "Failed to encode frame.\n");
        retval = AVERROR_INVALIDDATA;
        goto done;
    } else
        retval = 0; /* kvazaar returns 1 on success */

    if (data_out) {
        kvz_data_chunk *chunk = NULL;
        uint64_t written = 0;

        retval = ff_alloc_packet2(avctx, avpkt, len_out, len_out);
        if (retval < 0) {
            av_log(avctx, AV_LOG_ERROR, "Failed to allocate output packet.\n");
            goto done;
        }

        for (chunk = data_out; chunk != NULL; chunk = chunk->next) {
            av_assert0(written + chunk->len <= len_out);
            memcpy(avpkt->data + written, chunk->data, chunk->len);
            written += chunk->len;
        }

        avpkt->pts = recon_pic->pts;
        avpkt->dts = recon_pic->dts;
        avpkt->flags = 0;
        // IRAP VCL NAL unit types span the range
        // [BLA_W_LP (16), RSV_IRAP_VCL23 (23)].
        if (frame_info.nal_unit_type >= KVZ_NAL_BLA_W_LP &&
            frame_info.nal_unit_type <= KVZ_NAL_RSV_IRAP_VCL23) {
            avpkt->flags |= AV_PKT_FLAG_KEY;
        }

        *got_packet_ptr = 1;
    }

done:
    ctx->api->picture_free(input_pic);
    ctx->api->picture_free(recon_pic);
    ctx->api->chunk_free(data_out);
    return retval;
}