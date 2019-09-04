#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int* linesize; scalar_t__ interlaced_frame; int /*<<< orphan*/ ** data; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* idct_put ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int bit_depth; int is_444; scalar_t__ (* decode_dct_block ) (TYPE_4__ const*,TYPE_3__*,int) ;TYPE_1__ idsp; TYPE_11__* avctx; scalar_t__ cur_field; TYPE_2__* cid_table; int /*<<< orphan*/  act; scalar_t__ mbaff; } ;
struct TYPE_15__ {int format; int last_qscale; int* luma_scale; int* chroma_scale; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  gb; } ;
struct TYPE_14__ {int* luma_weight; int* chroma_weight; } ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_3__ RowContext ;
typedef  TYPE_4__ DNXHDContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__ const*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnxhd_decode_macroblock(const DNXHDContext *ctx, RowContext *row,
                                   AVFrame *frame, int x, int y)
{
    int shift1 = ctx->bit_depth >= 10;
    int dct_linesize_luma   = frame->linesize[0];
    int dct_linesize_chroma = frame->linesize[1];
    uint8_t *dest_y, *dest_u, *dest_v;
    int dct_y_offset, dct_x_offset;
    int qscale, i, act;
    int interlaced_mb = 0;

    if (ctx->mbaff) {
        interlaced_mb = get_bits1(&row->gb);
        qscale = get_bits(&row->gb, 10);
    } else {
        qscale = get_bits(&row->gb, 11);
    }
    act = get_bits1(&row->gb);
    if (act) {
        if (!ctx->act) {
            static int act_warned;
            if (!act_warned) {
                act_warned = 1;
                av_log(ctx->avctx, AV_LOG_ERROR,
                       "ACT flag set, in violation of frame header.\n");
            }
        } else if (row->format == -1) {
            row->format = act;
        } else if (row->format != act) {
            row->format = 2; // Variable
        }
    }

    if (qscale != row->last_qscale) {
        for (i = 0; i < 64; i++) {
            row->luma_scale[i]   = qscale * ctx->cid_table->luma_weight[i];
            row->chroma_scale[i] = qscale * ctx->cid_table->chroma_weight[i];
        }
        row->last_qscale = qscale;
    }

    for (i = 0; i < 8 + 4 * ctx->is_444; i++) {
        if (ctx->decode_dct_block(ctx, row, i) < 0)
            return AVERROR_INVALIDDATA;
    }

    if (frame->interlaced_frame) {
        dct_linesize_luma   <<= 1;
        dct_linesize_chroma <<= 1;
    }

    dest_y = frame->data[0] + ((y * dct_linesize_luma)   << 4) + (x << (4 + shift1));
    dest_u = frame->data[1] + ((y * dct_linesize_chroma) << 4) + (x << (3 + shift1 + ctx->is_444));
    dest_v = frame->data[2] + ((y * dct_linesize_chroma) << 4) + (x << (3 + shift1 + ctx->is_444));

    if (frame->interlaced_frame && ctx->cur_field) {
        dest_y += frame->linesize[0];
        dest_u += frame->linesize[1];
        dest_v += frame->linesize[2];
    }
    if (interlaced_mb) {
        dct_linesize_luma   <<= 1;
        dct_linesize_chroma <<= 1;
    }

    dct_y_offset = interlaced_mb ? frame->linesize[0] : (dct_linesize_luma << 3);
    dct_x_offset = 8 << shift1;
    if (!ctx->is_444) {
        ctx->idsp.idct_put(dest_y,                               dct_linesize_luma, row->blocks[0]);
        ctx->idsp.idct_put(dest_y + dct_x_offset,                dct_linesize_luma, row->blocks[1]);
        ctx->idsp.idct_put(dest_y + dct_y_offset,                dct_linesize_luma, row->blocks[4]);
        ctx->idsp.idct_put(dest_y + dct_y_offset + dct_x_offset, dct_linesize_luma, row->blocks[5]);

        if (!(ctx->avctx->flags & AV_CODEC_FLAG_GRAY)) {
            dct_y_offset = interlaced_mb ? frame->linesize[1] : (dct_linesize_chroma << 3);
            ctx->idsp.idct_put(dest_u,                dct_linesize_chroma, row->blocks[2]);
            ctx->idsp.idct_put(dest_v,                dct_linesize_chroma, row->blocks[3]);
            ctx->idsp.idct_put(dest_u + dct_y_offset, dct_linesize_chroma, row->blocks[6]);
            ctx->idsp.idct_put(dest_v + dct_y_offset, dct_linesize_chroma, row->blocks[7]);
        }
    } else {
        ctx->idsp.idct_put(dest_y,                               dct_linesize_luma, row->blocks[0]);
        ctx->idsp.idct_put(dest_y + dct_x_offset,                dct_linesize_luma, row->blocks[1]);
        ctx->idsp.idct_put(dest_y + dct_y_offset,                dct_linesize_luma, row->blocks[6]);
        ctx->idsp.idct_put(dest_y + dct_y_offset + dct_x_offset, dct_linesize_luma, row->blocks[7]);

        if (!(ctx->avctx->flags & AV_CODEC_FLAG_GRAY)) {
            dct_y_offset = interlaced_mb ? frame->linesize[1] : (dct_linesize_chroma << 3);
            ctx->idsp.idct_put(dest_u,                               dct_linesize_chroma, row->blocks[2]);
            ctx->idsp.idct_put(dest_u + dct_x_offset,                dct_linesize_chroma, row->blocks[3]);
            ctx->idsp.idct_put(dest_u + dct_y_offset,                dct_linesize_chroma, row->blocks[8]);
            ctx->idsp.idct_put(dest_u + dct_y_offset + dct_x_offset, dct_linesize_chroma, row->blocks[9]);
            ctx->idsp.idct_put(dest_v,                               dct_linesize_chroma, row->blocks[4]);
            ctx->idsp.idct_put(dest_v + dct_x_offset,                dct_linesize_chroma, row->blocks[5]);
            ctx->idsp.idct_put(dest_v + dct_y_offset,                dct_linesize_chroma, row->blocks[10]);
            ctx->idsp.idct_put(dest_v + dct_y_offset + dct_x_offset, dct_linesize_chroma, row->blocks[11]);
        }
    }

    return 0;
}