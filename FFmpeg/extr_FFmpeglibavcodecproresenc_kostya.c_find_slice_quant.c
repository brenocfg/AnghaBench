#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_19__ {int width; int height; TYPE_5__* priv_data; } ;
struct TYPE_18__ {int pictures_per_frame; int cur_picture_idx; int num_planes; int chroma_factor; int** quants; int** quants_chroma; int bits_per_mb; int* quant_mat; int* quant_chroma_mat; scalar_t__ alpha_bits; TYPE_1__* pic; TYPE_3__* profile_info; } ;
struct TYPE_17__ {int* custom_q; int* custom_chroma_q; TYPE_2__* nodes; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  emu_buf; } ;
struct TYPE_16__ {int min_quant; int max_quant; } ;
struct TYPE_15__ {int prev_node; int quant; int bits; int score; } ;
struct TYPE_14__ {int* linesize; scalar_t__* data; int /*<<< orphan*/  top_field_first; } ;
typedef  TYPE_4__ ProresThreadData ;
typedef  TYPE_5__ ProresContext ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int CFACTOR_Y444 ; 
 int MAX_PLANES ; 
 int MAX_STORED_Q ; 
 int SCORE_LIMIT ; 
 int TRELLIS_WIDTH ; 
 int av_log2 (int) ; 
 int estimate_alpha_plane (TYPE_5__*,int const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ estimate_slice_plane (TYPE_5__*,int*,int,int const*,int,int,int,int,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  get_alpha_data (TYPE_5__*,int const*,int,int,int,int,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  get_slice_data (TYPE_5__*,int const*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int find_slice_quant(AVCodecContext *avctx,
                            int trellis_node, int x, int y, int mbs_per_slice,
                            ProresThreadData *td)
{
    ProresContext *ctx = avctx->priv_data;
    int i, q, pq, xp, yp;
    const uint16_t *src;
    int slice_width_factor = av_log2(mbs_per_slice);
    int num_cblocks[MAX_PLANES], pwidth;
    int plane_factor[MAX_PLANES], is_chroma[MAX_PLANES];
    const int min_quant = ctx->profile_info->min_quant;
    const int max_quant = ctx->profile_info->max_quant;
    int error, bits, bits_limit;
    int mbs, prev, cur, new_score;
    int slice_bits[TRELLIS_WIDTH], slice_score[TRELLIS_WIDTH];
    int overquant;
    uint16_t *qmat;
    uint16_t *qmat_chroma;
    int linesize[4], line_add;
    int alpha_bits = 0;

    if (ctx->pictures_per_frame == 1)
        line_add = 0;
    else
        line_add = ctx->cur_picture_idx ^ !ctx->pic->top_field_first;
    mbs = x + mbs_per_slice;

    for (i = 0; i < ctx->num_planes; i++) {
        is_chroma[i]    = (i == 1 || i == 2);
        plane_factor[i] = slice_width_factor + 2;
        if (is_chroma[i])
            plane_factor[i] += ctx->chroma_factor - 3;
        if (!is_chroma[i] || ctx->chroma_factor == CFACTOR_Y444) {
            xp             = x << 4;
            yp             = y << 4;
            num_cblocks[i] = 4;
            pwidth         = avctx->width;
        } else {
            xp             = x << 3;
            yp             = y << 4;
            num_cblocks[i] = 2;
            pwidth         = avctx->width >> 1;
        }

        linesize[i] = ctx->pic->linesize[i] * ctx->pictures_per_frame;
        src = (const uint16_t *)(ctx->pic->data[i] + yp * linesize[i] +
                                 line_add * ctx->pic->linesize[i]) + xp;

        if (i < 3) {
            get_slice_data(ctx, src, linesize[i], xp, yp,
                           pwidth, avctx->height / ctx->pictures_per_frame,
                           td->blocks[i], td->emu_buf,
                           mbs_per_slice, num_cblocks[i], is_chroma[i]);
        } else {
            get_alpha_data(ctx, src, linesize[i], xp, yp,
                           pwidth, avctx->height / ctx->pictures_per_frame,
                           td->blocks[i], mbs_per_slice, ctx->alpha_bits);
        }
    }

    for (q = min_quant; q < max_quant + 2; q++) {
        td->nodes[trellis_node + q].prev_node = -1;
        td->nodes[trellis_node + q].quant     = q;
    }

    if (ctx->alpha_bits)
        alpha_bits = estimate_alpha_plane(ctx, src, linesize[3],
                                          mbs_per_slice, td->blocks[3]);
    // todo: maybe perform coarser quantising to fit into frame size when needed
    for (q = min_quant; q <= max_quant; q++) {
        bits  = alpha_bits;
        error = 0;
        bits += estimate_slice_plane(ctx, &error, 0,
                                     src, linesize[0],
                                     mbs_per_slice,
                                     num_cblocks[0], plane_factor[0],
                                     ctx->quants[q], td); /* estimate luma plane */
        for (i = 1; i < ctx->num_planes - !!ctx->alpha_bits; i++) { /* estimate chroma plane */
            bits += estimate_slice_plane(ctx, &error, i,
                                         src, linesize[i],
                                         mbs_per_slice,
                                         num_cblocks[i], plane_factor[i],
                                         ctx->quants_chroma[q], td);
        }
        if (bits > 65000 * 8)
            error = SCORE_LIMIT;

        slice_bits[q]  = bits;
        slice_score[q] = error;
    }
    if (slice_bits[max_quant] <= ctx->bits_per_mb * mbs_per_slice) {
        slice_bits[max_quant + 1]  = slice_bits[max_quant];
        slice_score[max_quant + 1] = slice_score[max_quant] + 1;
        overquant = max_quant;
    } else {
        for (q = max_quant + 1; q < 128; q++) {
            bits  = alpha_bits;
            error = 0;
            if (q < MAX_STORED_Q) {
                qmat = ctx->quants[q];
                qmat_chroma = ctx->quants_chroma[q];
            } else {
                qmat = td->custom_q;
                qmat_chroma = td->custom_chroma_q;
                for (i = 0; i < 64; i++) {
                    qmat[i] = ctx->quant_mat[i] * q;
                    qmat_chroma[i] = ctx->quant_chroma_mat[i] * q;
                }
            }
            bits += estimate_slice_plane(ctx, &error, 0,
                                         src, linesize[0],
                                         mbs_per_slice,
                                         num_cblocks[0], plane_factor[0],
                                         qmat, td);/* estimate luma plane */
            for (i = 1; i < ctx->num_planes - !!ctx->alpha_bits; i++) { /* estimate chroma plane */
                bits += estimate_slice_plane(ctx, &error, i,
                                             src, linesize[i],
                                             mbs_per_slice,
                                             num_cblocks[i], plane_factor[i],
                                             qmat_chroma, td);
            }
            if (bits <= ctx->bits_per_mb * mbs_per_slice)
                break;
        }

        slice_bits[max_quant + 1]  = bits;
        slice_score[max_quant + 1] = error;
        overquant = q;
    }
    td->nodes[trellis_node + max_quant + 1].quant = overquant;

    bits_limit = mbs * ctx->bits_per_mb;
    for (pq = min_quant; pq < max_quant + 2; pq++) {
        prev = trellis_node - TRELLIS_WIDTH + pq;

        for (q = min_quant; q < max_quant + 2; q++) {
            cur = trellis_node + q;

            bits  = td->nodes[prev].bits + slice_bits[q];
            error = slice_score[q];
            if (bits > bits_limit)
                error = SCORE_LIMIT;

            if (td->nodes[prev].score < SCORE_LIMIT && error < SCORE_LIMIT)
                new_score = td->nodes[prev].score + error;
            else
                new_score = SCORE_LIMIT;
            if (td->nodes[cur].prev_node == -1 ||
                td->nodes[cur].score >= new_score) {

                td->nodes[cur].bits      = bits;
                td->nodes[cur].score     = new_score;
                td->nodes[cur].prev_node = prev;
            }
        }
    }

    error = td->nodes[trellis_node + min_quant].score;
    pq    = trellis_node + min_quant;
    for (q = min_quant + 1; q < max_quant + 2; q++) {
        if (td->nodes[trellis_node + q].score <= error) {
            error = td->nodes[trellis_node + q].score;
            pq    = trellis_node + q;
        }
    }

    return pq;
}