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
struct TYPE_4__ {int prev_frame_type; int frame_type; int frame_num; int gop_invalid; int frame_flags; int checksum; int /*<<< orphan*/  gb; int /*<<< orphan*/  mb_vlc; int /*<<< orphan*/  pic_hdr_size; int /*<<< orphan*/  is_scalable; } ;
typedef  TYPE_1__ IVI45DecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FRAMETYPE_INTER ; 
 int FRAMETYPE_INTER_SCAL ; 
 int FRAMETYPE_INTRA ; 
 int FRAMETYPE_NULL ; 
 int /*<<< orphan*/  IVI_MB_HUFF ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int decode_gop_header (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int ff_ivi_dec_huff_desc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_hdr_extension (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_pic_hdr(IVI45DecContext *ctx, AVCodecContext *avctx)
{
    int ret;

    if (get_bits(&ctx->gb, 5) != 0x1F) {
        av_log(avctx, AV_LOG_ERROR, "Invalid picture start code!\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->prev_frame_type = ctx->frame_type;
    ctx->frame_type      = get_bits(&ctx->gb, 3);
    if (ctx->frame_type >= 5) {
        av_log(avctx, AV_LOG_ERROR, "Invalid frame type: %d \n", ctx->frame_type);
        ctx->frame_type = FRAMETYPE_INTRA;
        return AVERROR_INVALIDDATA;
    }

    ctx->frame_num = get_bits(&ctx->gb, 8);

    if (ctx->frame_type == FRAMETYPE_INTRA) {
        if ((ret = decode_gop_header(ctx, avctx)) < 0) {
            av_log(avctx, AV_LOG_ERROR, "Invalid GOP header, skipping frames.\n");
            ctx->gop_invalid = 1;
            return ret;
        }
        ctx->gop_invalid = 0;
    }

    if (ctx->frame_type == FRAMETYPE_INTER_SCAL && !ctx->is_scalable) {
        av_log(avctx, AV_LOG_ERROR, "Scalable inter frame in non scalable stream\n");
        ctx->frame_type = FRAMETYPE_INTER;
        return AVERROR_INVALIDDATA;
    }

    if (ctx->frame_type != FRAMETYPE_NULL) {
        ctx->frame_flags = get_bits(&ctx->gb, 8);

        ctx->pic_hdr_size = (ctx->frame_flags & 1) ? get_bits_long(&ctx->gb, 24) : 0;

        ctx->checksum = (ctx->frame_flags & 0x10) ? get_bits(&ctx->gb, 16) : 0;

        /* skip unknown extension if any */
        if (ctx->frame_flags & 0x20)
            skip_hdr_extension(&ctx->gb); /* XXX: untested */

        /* decode macroblock huffman codebook */
        ret = ff_ivi_dec_huff_desc(&ctx->gb, ctx->frame_flags & 0x40,
                                   IVI_MB_HUFF, &ctx->mb_vlc, avctx);
        if (ret < 0)
            return ret;

        skip_bits(&ctx->gb, 3); /* FIXME: unknown meaning! */
    }

    align_get_bits(&ctx->gb);

    return 0;
}