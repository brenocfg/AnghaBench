#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int ptrdiff_t ;
struct TYPE_13__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int* linesize; scalar_t__* data; int /*<<< orphan*/  top_field_first; } ;
struct TYPE_11__ {int pictures_per_frame; int cur_picture_idx; int** quants; int** quants_chroma; int* custom_q; int* custom_chroma_q; int* quant_mat; int* quant_chroma_mat; int num_planes; int chroma_factor; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  alpha_bits; int /*<<< orphan*/  emu_buf; scalar_t__ force_quant; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ ProresContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int CFACTOR_Y444 ; 
 int MAX_STORED_Q ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_log2 (int) ; 
 int encode_alpha_plane (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int encode_slice_plane (TYPE_1__*,int /*<<< orphan*/ *,int const*,int,int,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  get_alpha_data (TYPE_1__*,int const*,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_slice_data (TYPE_1__*,int const*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ put_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encode_slice(AVCodecContext *avctx, const AVFrame *pic,
                        PutBitContext *pb,
                        int sizes[4], int x, int y, int quant,
                        int mbs_per_slice)
{
    ProresContext *ctx = avctx->priv_data;
    int i, xp, yp;
    int total_size = 0;
    const uint16_t *src;
    int slice_width_factor = av_log2(mbs_per_slice);
    int num_cblocks, pwidth, line_add;
    ptrdiff_t linesize;
    int plane_factor, is_chroma;
    uint16_t *qmat;
    uint16_t *qmat_chroma;

    if (ctx->pictures_per_frame == 1)
        line_add = 0;
    else
        line_add = ctx->cur_picture_idx ^ !pic->top_field_first;

    if (ctx->force_quant) {
        qmat = ctx->quants[0];
        qmat_chroma = ctx->quants_chroma[0];
    } else if (quant < MAX_STORED_Q) {
        qmat = ctx->quants[quant];
        qmat_chroma = ctx->quants_chroma[quant];
    } else {
        qmat = ctx->custom_q;
        qmat_chroma = ctx->custom_chroma_q;
        for (i = 0; i < 64; i++) {
            qmat[i] = ctx->quant_mat[i] * quant;
            qmat_chroma[i] = ctx->quant_chroma_mat[i] * quant;
        }
    }

    for (i = 0; i < ctx->num_planes; i++) {
        is_chroma    = (i == 1 || i == 2);
        plane_factor = slice_width_factor + 2;
        if (is_chroma)
            plane_factor += ctx->chroma_factor - 3;
        if (!is_chroma || ctx->chroma_factor == CFACTOR_Y444) {
            xp          = x << 4;
            yp          = y << 4;
            num_cblocks = 4;
            pwidth      = avctx->width;
        } else {
            xp          = x << 3;
            yp          = y << 4;
            num_cblocks = 2;
            pwidth      = avctx->width >> 1;
        }

        linesize = pic->linesize[i] * ctx->pictures_per_frame;
        src = (const uint16_t*)(pic->data[i] + yp * linesize +
                                line_add * pic->linesize[i]) + xp;

        if (i < 3) {
            get_slice_data(ctx, src, linesize, xp, yp,
                           pwidth, avctx->height / ctx->pictures_per_frame,
                           ctx->blocks[0], ctx->emu_buf,
                           mbs_per_slice, num_cblocks, is_chroma);
            if (!is_chroma) {/* luma quant */
                sizes[i] = encode_slice_plane(ctx, pb, src, linesize,
                                              mbs_per_slice, ctx->blocks[0],
                                              num_cblocks, plane_factor,
                                              qmat);
            } else { /* chroma plane */
                sizes[i] = encode_slice_plane(ctx, pb, src, linesize,
                                              mbs_per_slice, ctx->blocks[0],
                                              num_cblocks, plane_factor,
                                              qmat_chroma);
            }
        } else {
            get_alpha_data(ctx, src, linesize, xp, yp,
                           pwidth, avctx->height / ctx->pictures_per_frame,
                           ctx->blocks[0], mbs_per_slice, ctx->alpha_bits);
            sizes[i] = encode_alpha_plane(ctx, pb, mbs_per_slice,
                                          ctx->blocks[0], quant);
        }
        total_size += sizes[i];
        if (put_bits_left(pb) < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Underestimated required buffer size.\n");
            return AVERROR_BUG;
        }
    }
    return total_size;
}