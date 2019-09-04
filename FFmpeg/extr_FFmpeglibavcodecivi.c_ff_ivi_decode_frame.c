#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_28__ {TYPE_1__* priv_data; } ;
struct TYPE_27__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int frame_size; int (* decode_pic_hdr ) (TYPE_1__*,TYPE_4__*) ;scalar_t__ frame_type; int got_p_frame; int gop_flags; int* buf_invalid; size_t dst_buf; scalar_t__ show_indeo4_info; scalar_t__ uses_fullpel; scalar_t__ uses_haar; scalar_t__ has_transp; scalar_t__ has_b_frames; scalar_t__ uses_tiling; scalar_t__ is_scalable; void* p_frame; int /*<<< orphan*/  gb; scalar_t__ is_indeo4; TYPE_10__* planes; scalar_t__ (* is_nonnull_frame ) (TYPE_1__*) ;int /*<<< orphan*/  (* switch_buffers ) (TYPE_1__*) ;scalar_t__ gop_invalid; int /*<<< orphan*/  const* frame_data; } ;
struct TYPE_24__ {int /*<<< orphan*/  buf; } ;
struct TYPE_23__ {int num_bands; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_19__* bands; } ;
typedef  TYPE_1__ IVI45DecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ IVI4_FRAMETYPE_INTRA ; 
 scalar_t__ IVI4_FRAMETYPE_NULL_LAST ; 
 int IVI5_IS_PROTECTED ; 
 int /*<<< orphan*/  av_frame_move_ref (void*,void*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*) ; 
 int decode_band (TYPE_1__*,TYPE_19__*,TYPE_4__*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ivi_recompose53 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ivi_recompose_haar (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ivi_output_plane (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 scalar_t__ stub3 (TYPE_1__*) ; 
 scalar_t__ stub4 (TYPE_1__*) ; 

int ff_ivi_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    IVI45DecContext *ctx = avctx->priv_data;
    const uint8_t   *buf = avpkt->data;
    AVFrame       *frame = data;
    int             buf_size = avpkt->size;
    int             result, p, b;

    result = init_get_bits8(&ctx->gb, buf, buf_size);
    if (result < 0)
        return result;
    ctx->frame_data = buf;
    ctx->frame_size = buf_size;

    result = ctx->decode_pic_hdr(ctx, avctx);
    if (result) {
        av_log(avctx, AV_LOG_ERROR,
               "Error while decoding picture header: %d\n", result);
        return result;
    }
    if (ctx->gop_invalid)
        return AVERROR_INVALIDDATA;

    if (ctx->is_indeo4 && ctx->frame_type == IVI4_FRAMETYPE_NULL_LAST) {
        if (ctx->got_p_frame) {
            av_frame_move_ref(data, ctx->p_frame);
            *got_frame = 1;
            ctx->got_p_frame = 0;
        } else {
            *got_frame = 0;
        }
        return buf_size;
    }

    if (ctx->gop_flags & IVI5_IS_PROTECTED) {
        avpriv_report_missing_feature(avctx, "Password-protected clip");
        return AVERROR_PATCHWELCOME;
    }

    if (!ctx->planes[0].bands) {
        av_log(avctx, AV_LOG_ERROR, "Color planes not initialized yet\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->switch_buffers(ctx);

    //{ START_TIMER;

    if (ctx->is_nonnull_frame(ctx)) {
        ctx->buf_invalid[ctx->dst_buf] = 1;
        for (p = 0; p < 3; p++) {
            for (b = 0; b < ctx->planes[p].num_bands; b++) {
                result = decode_band(ctx, &ctx->planes[p].bands[b], avctx);
                if (result < 0) {
                    av_log(avctx, AV_LOG_ERROR,
                           "Error while decoding band: %d, plane: %d\n", b, p);
                    return result;
                }
            }
        }
        ctx->buf_invalid[ctx->dst_buf] = 0;
    } else {
        if (ctx->is_scalable)
            return AVERROR_INVALIDDATA;

        for (p = 0; p < 3; p++) {
            if (!ctx->planes[p].bands[0].buf)
                return AVERROR_INVALIDDATA;
        }
    }
    if (ctx->buf_invalid[ctx->dst_buf])
        return -1;

    //STOP_TIMER("decode_planes"); }

    if (!ctx->is_nonnull_frame(ctx))
        return buf_size;

    result = ff_set_dimensions(avctx, ctx->planes[0].width, ctx->planes[0].height);
    if (result < 0)
        return result;

    if ((result = ff_get_buffer(avctx, frame, 0)) < 0)
        return result;

    if (ctx->is_scalable) {
        if (ctx->is_indeo4)
            ff_ivi_recompose_haar(&ctx->planes[0], frame->data[0], frame->linesize[0]);
        else
            ff_ivi_recompose53   (&ctx->planes[0], frame->data[0], frame->linesize[0]);
    } else {
        ivi_output_plane(&ctx->planes[0], frame->data[0], frame->linesize[0]);
    }

    ivi_output_plane(&ctx->planes[2], frame->data[1], frame->linesize[1]);
    ivi_output_plane(&ctx->planes[1], frame->data[2], frame->linesize[2]);

    *got_frame = 1;

    /* If the bidirectional mode is enabled, next I and the following P
     * frame will be sent together. Unfortunately the approach below seems
     * to be the only way to handle the B-frames mode.
     * That's exactly the same Intel decoders do.
     */
    if (ctx->is_indeo4 && ctx->frame_type == IVI4_FRAMETYPE_INTRA) {
        int left;

            // skip version string
        while (get_bits(&ctx->gb, 8)) {
            if (get_bits_left(&ctx->gb) < 8)
                return AVERROR_INVALIDDATA;
        }
        left = get_bits_count(&ctx->gb) & 0x18;
        skip_bits_long(&ctx->gb, 64 - left);
        if (get_bits_left(&ctx->gb) > 18 &&
            show_bits_long(&ctx->gb, 21) == 0xBFFF8) { // syncheader + inter type
            AVPacket pkt;
            pkt.data = avpkt->data + (get_bits_count(&ctx->gb) >> 3);
            pkt.size = get_bits_left(&ctx->gb) >> 3;
            ff_ivi_decode_frame(avctx, ctx->p_frame, &ctx->got_p_frame, &pkt);
        }
    }

    if (ctx->show_indeo4_info) {
        if (ctx->is_scalable)
            av_log(avctx, AV_LOG_DEBUG, "This video uses scalability mode\n");
        if (ctx->uses_tiling)
            av_log(avctx, AV_LOG_DEBUG, "This video uses local decoding\n");
        if (ctx->has_b_frames)
            av_log(avctx, AV_LOG_DEBUG, "This video contains B-frames\n");
        if (ctx->has_transp)
            av_log(avctx, AV_LOG_DEBUG, "Transparency mode is enabled\n");
        if (ctx->uses_haar)
            av_log(avctx, AV_LOG_DEBUG, "This video uses Haar transform\n");
        if (ctx->uses_fullpel)
            av_log(avctx, AV_LOG_DEBUG, "This video uses fullpel motion vectors\n");
        ctx->show_indeo4_info = 0;
    }

    return buf_size;
}