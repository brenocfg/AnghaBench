#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int int64_t ;
struct TYPE_26__ {int tile_col_start; int /*<<< orphan*/ * c; int /*<<< orphan*/ * c_b; int /*<<< orphan*/  left_segpred_ctx; int /*<<< orphan*/  left_uv_nnz_ctx; int /*<<< orphan*/  left_y_nnz_ctx; int /*<<< orphan*/  left_mode_ctx; int /*<<< orphan*/  left_skip_ctx; int /*<<< orphan*/  left_partition_ctx; } ;
typedef  TYPE_6__ VP9TileData ;
struct TYPE_27__ {int /*<<< orphan*/  mask; } ;
typedef  TYPE_7__ VP9Filter ;
struct TYPE_21__ {scalar_t__ level; } ;
struct TYPE_23__ {int tile_rows; int tile_cols; int /*<<< orphan*/  log2_tile_cols; int /*<<< orphan*/  log2_tile_rows; } ;
struct TYPE_24__ {TYPE_1__ filter; scalar_t__ intraonly; scalar_t__ keyframe; TYPE_3__ tiling; } ;
struct TYPE_25__ {TYPE_2__* frames; TYPE_4__ h; } ;
struct TYPE_28__ {int bytesperpixel; int ss_v; int pass; int ss_h; int rows; int cols; TYPE_5__ s; TYPE_7__* lflvl; int /*<<< orphan*/ * intra_pred_data; int /*<<< orphan*/  sb_cols; int /*<<< orphan*/  sb_rows; TYPE_6__* td; } ;
typedef  TYPE_8__ VP9Context ;
struct TYPE_29__ {int* linesize; scalar_t__* data; } ;
struct TYPE_20__ {TYPE_9__* f; } ;
struct TYPE_22__ {TYPE_13__ tf; } ;
struct TYPE_19__ {TYPE_8__* priv_data; } ;
typedef  TYPE_9__ AVFrame ;
typedef  TYPE_10__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BL_64X64 ; 
 size_t CUR_FRAME ; 
 int /*<<< orphan*/  DC_PRED ; 
 int INT_MAX ; 
 int /*<<< orphan*/  NEARESTMV ; 
 int /*<<< orphan*/  decode_sb (TYPE_6__*,int,int,TYPE_7__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_sb_mem (TYPE_6__*,int,int,TYPE_7__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_thread_report_progress (TYPE_13__*,int,int /*<<< orphan*/ ) ; 
 int ff_vp56_init_range_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ff_vp9_loopfilter_sb (TYPE_10__*,TYPE_7__*,int,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_tile_offset (int*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vpX_rac_is_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_tiles(AVCodecContext *avctx,
                        const uint8_t *data, int size)
{
    VP9Context *s = avctx->priv_data;
    VP9TileData *td = &s->td[0];
    int row, col, tile_row, tile_col, ret;
    int bytesperpixel;
    int tile_row_start, tile_row_end, tile_col_start, tile_col_end;
    AVFrame *f;
    ptrdiff_t yoff, uvoff, ls_y, ls_uv;

    f = s->s.frames[CUR_FRAME].tf.f;
    ls_y = f->linesize[0];
    ls_uv =f->linesize[1];
    bytesperpixel = s->bytesperpixel;

    yoff = uvoff = 0;
    for (tile_row = 0; tile_row < s->s.h.tiling.tile_rows; tile_row++) {
        set_tile_offset(&tile_row_start, &tile_row_end,
                        tile_row, s->s.h.tiling.log2_tile_rows, s->sb_rows);

        for (tile_col = 0; tile_col < s->s.h.tiling.tile_cols; tile_col++) {
            int64_t tile_size;

            if (tile_col == s->s.h.tiling.tile_cols - 1 &&
                tile_row == s->s.h.tiling.tile_rows - 1) {
                tile_size = size;
            } else {
                tile_size = AV_RB32(data);
                data += 4;
                size -= 4;
            }
            if (tile_size > size) {
                ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);
                return AVERROR_INVALIDDATA;
            }
            ret = ff_vp56_init_range_decoder(&td->c_b[tile_col], data, tile_size);
            if (ret < 0)
                return ret;
            if (vp56_rac_get_prob_branchy(&td->c_b[tile_col], 128)) { // marker bit
                ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);
                return AVERROR_INVALIDDATA;
            }
            data += tile_size;
            size -= tile_size;
        }

        for (row = tile_row_start; row < tile_row_end;
             row += 8, yoff += ls_y * 64, uvoff += ls_uv * 64 >> s->ss_v) {
            VP9Filter *lflvl_ptr = s->lflvl;
            ptrdiff_t yoff2 = yoff, uvoff2 = uvoff;

            for (tile_col = 0; tile_col < s->s.h.tiling.tile_cols; tile_col++) {
                set_tile_offset(&tile_col_start, &tile_col_end,
                                tile_col, s->s.h.tiling.log2_tile_cols, s->sb_cols);
                td->tile_col_start = tile_col_start;
                if (s->pass != 2) {
                    memset(td->left_partition_ctx, 0, 8);
                    memset(td->left_skip_ctx, 0, 8);
                    if (s->s.h.keyframe || s->s.h.intraonly) {
                        memset(td->left_mode_ctx, DC_PRED, 16);
                    } else {
                        memset(td->left_mode_ctx, NEARESTMV, 8);
                    }
                    memset(td->left_y_nnz_ctx, 0, 16);
                    memset(td->left_uv_nnz_ctx, 0, 32);
                    memset(td->left_segpred_ctx, 0, 8);

                    td->c = &td->c_b[tile_col];
                }

                for (col = tile_col_start;
                     col < tile_col_end;
                     col += 8, yoff2 += 64 * bytesperpixel,
                     uvoff2 += 64 * bytesperpixel >> s->ss_h, lflvl_ptr++) {
                    // FIXME integrate with lf code (i.e. zero after each
                    // use, similar to invtxfm coefficients, or similar)
                    if (s->pass != 1) {
                        memset(lflvl_ptr->mask, 0, sizeof(lflvl_ptr->mask));
                    }

                    if (s->pass == 2) {
                        decode_sb_mem(td, row, col, lflvl_ptr,
                                      yoff2, uvoff2, BL_64X64);
                    } else {
                        if (vpX_rac_is_end(td->c)) {
                            return AVERROR_INVALIDDATA;
                        }
                        decode_sb(td, row, col, lflvl_ptr,
                                  yoff2, uvoff2, BL_64X64);
                    }
                }
            }

            if (s->pass == 1)
                continue;

            // backup pre-loopfilter reconstruction data for intra
            // prediction of next row of sb64s
            if (row + 8 < s->rows) {
                memcpy(s->intra_pred_data[0],
                       f->data[0] + yoff + 63 * ls_y,
                       8 * s->cols * bytesperpixel);
                memcpy(s->intra_pred_data[1],
                       f->data[1] + uvoff + ((64 >> s->ss_v) - 1) * ls_uv,
                       8 * s->cols * bytesperpixel >> s->ss_h);
                memcpy(s->intra_pred_data[2],
                       f->data[2] + uvoff + ((64 >> s->ss_v) - 1) * ls_uv,
                       8 * s->cols * bytesperpixel >> s->ss_h);
            }

            // loopfilter one row
            if (s->s.h.filter.level) {
                yoff2 = yoff;
                uvoff2 = uvoff;
                lflvl_ptr = s->lflvl;
                for (col = 0; col < s->cols;
                     col += 8, yoff2 += 64 * bytesperpixel,
                     uvoff2 += 64 * bytesperpixel >> s->ss_h, lflvl_ptr++) {
                    ff_vp9_loopfilter_sb(avctx, lflvl_ptr, row, col,
                                         yoff2, uvoff2);
                }
            }

            // FIXME maybe we can make this more finegrained by running the
            // loopfilter per-block instead of after each sbrow
            // In fact that would also make intra pred left preparation easier?
            ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, row >> 3, 0);
        }
    }
    return 0;
}