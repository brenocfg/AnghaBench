#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {void* pred_y; void* pred_x; TYPE_3__* preds; } ;
struct TYPE_19__ {int nb; void*** mvs; } ;
struct TYPE_18__ {int** mvs; } ;
struct TYPE_17__ {int b_width; int log2_mb_size; int me_method; int**** mv_table; int b_height; TYPE_4__ me_ctx; } ;
typedef  TYPE_1__ MIContext ;
typedef  TYPE_2__ Block ;
typedef  TYPE_3__ AVMotionEstPredictor ;
typedef  TYPE_4__ AVMotionEstContext ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PRED (TYPE_3__,int,int) ; 
#define  AV_ME_METHOD_DS 136 
#define  AV_ME_METHOD_EPZS 135 
#define  AV_ME_METHOD_ESA 134 
#define  AV_ME_METHOD_FSS 133 
#define  AV_ME_METHOD_HEXBS 132 
#define  AV_ME_METHOD_NTSS 131 
#define  AV_ME_METHOD_TDLS 130 
#define  AV_ME_METHOD_TSS 129 
#define  AV_ME_METHOD_UMH 128 
 int /*<<< orphan*/  ff_me_search_ds (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_epzs (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_esa (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_fss (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_hexbs (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_ntss (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_tdls (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_tss (TYPE_4__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_umh (TYPE_4__*,int const,int const,int*) ; 
 void* mid_pred (void*,void*,void*) ; 

__attribute__((used)) static void search_mv(MIContext *mi_ctx, Block *blocks, int mb_x, int mb_y, int dir)
{
    AVMotionEstContext *me_ctx = &mi_ctx->me_ctx;
    AVMotionEstPredictor *preds = me_ctx->preds;
    Block *block = &blocks[mb_x + mb_y * mi_ctx->b_width];

    const int x_mb = mb_x << mi_ctx->log2_mb_size;
    const int y_mb = mb_y << mi_ctx->log2_mb_size;
    const int mb_i = mb_x + mb_y * mi_ctx->b_width;
    int mv[2] = {x_mb, y_mb};

    switch (mi_ctx->me_method) {
        case AV_ME_METHOD_ESA:
            ff_me_search_esa(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_TSS:
            ff_me_search_tss(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_TDLS:
            ff_me_search_tdls(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_NTSS:
            ff_me_search_ntss(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_FSS:
            ff_me_search_fss(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_DS:
            ff_me_search_ds(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_HEXBS:
            ff_me_search_hexbs(me_ctx, x_mb, y_mb, mv);
            break;
        case AV_ME_METHOD_EPZS:

            preds[0].nb = 0;
            preds[1].nb = 0;

            ADD_PRED(preds[0], 0, 0);

            //left mb in current frame
            if (mb_x > 0)
                ADD_PRED(preds[0], mi_ctx->mv_table[0][mb_i - 1][dir][0], mi_ctx->mv_table[0][mb_i - 1][dir][1]);

            //top mb in current frame
            if (mb_y > 0)
                ADD_PRED(preds[0], mi_ctx->mv_table[0][mb_i - mi_ctx->b_width][dir][0], mi_ctx->mv_table[0][mb_i - mi_ctx->b_width][dir][1]);

            //top-right mb in current frame
            if (mb_y > 0 && mb_x + 1 < mi_ctx->b_width)
                ADD_PRED(preds[0], mi_ctx->mv_table[0][mb_i - mi_ctx->b_width + 1][dir][0], mi_ctx->mv_table[0][mb_i - mi_ctx->b_width + 1][dir][1]);

            //median predictor
            if (preds[0].nb == 4) {
                me_ctx->pred_x = mid_pred(preds[0].mvs[1][0], preds[0].mvs[2][0], preds[0].mvs[3][0]);
                me_ctx->pred_y = mid_pred(preds[0].mvs[1][1], preds[0].mvs[2][1], preds[0].mvs[3][1]);
            } else if (preds[0].nb == 3) {
                me_ctx->pred_x = mid_pred(0, preds[0].mvs[1][0], preds[0].mvs[2][0]);
                me_ctx->pred_y = mid_pred(0, preds[0].mvs[1][1], preds[0].mvs[2][1]);
            } else if (preds[0].nb == 2) {
                me_ctx->pred_x = preds[0].mvs[1][0];
                me_ctx->pred_y = preds[0].mvs[1][1];
            } else {
                me_ctx->pred_x = 0;
                me_ctx->pred_y = 0;
            }

            //collocated mb in prev frame
            ADD_PRED(preds[0], mi_ctx->mv_table[1][mb_i][dir][0], mi_ctx->mv_table[1][mb_i][dir][1]);

            //accelerator motion vector of collocated block in prev frame
            ADD_PRED(preds[1], mi_ctx->mv_table[1][mb_i][dir][0] + (mi_ctx->mv_table[1][mb_i][dir][0] - mi_ctx->mv_table[2][mb_i][dir][0]),
                               mi_ctx->mv_table[1][mb_i][dir][1] + (mi_ctx->mv_table[1][mb_i][dir][1] - mi_ctx->mv_table[2][mb_i][dir][1]));

            //left mb in prev frame
            if (mb_x > 0)
                ADD_PRED(preds[1], mi_ctx->mv_table[1][mb_i - 1][dir][0], mi_ctx->mv_table[1][mb_i - 1][dir][1]);

            //top mb in prev frame
            if (mb_y > 0)
                ADD_PRED(preds[1], mi_ctx->mv_table[1][mb_i - mi_ctx->b_width][dir][0], mi_ctx->mv_table[1][mb_i - mi_ctx->b_width][dir][1]);

            //right mb in prev frame
            if (mb_x + 1 < mi_ctx->b_width)
                ADD_PRED(preds[1], mi_ctx->mv_table[1][mb_i + 1][dir][0], mi_ctx->mv_table[1][mb_i + 1][dir][1]);

            //bottom mb in prev frame
            if (mb_y + 1 < mi_ctx->b_height)
                ADD_PRED(preds[1], mi_ctx->mv_table[1][mb_i + mi_ctx->b_width][dir][0], mi_ctx->mv_table[1][mb_i + mi_ctx->b_width][dir][1]);

            ff_me_search_epzs(me_ctx, x_mb, y_mb, mv);

            mi_ctx->mv_table[0][mb_i][dir][0] = mv[0] - x_mb;
            mi_ctx->mv_table[0][mb_i][dir][1] = mv[1] - y_mb;

            break;
        case AV_ME_METHOD_UMH:

            preds[0].nb = 0;

            ADD_PRED(preds[0], 0, 0);

            //left mb in current frame
            if (mb_x > 0)
                ADD_PRED(preds[0], blocks[mb_i - 1].mvs[dir][0], blocks[mb_i - 1].mvs[dir][1]);

            if (mb_y > 0) {
                //top mb in current frame
                ADD_PRED(preds[0], blocks[mb_i - mi_ctx->b_width].mvs[dir][0], blocks[mb_i - mi_ctx->b_width].mvs[dir][1]);

                //top-right mb in current frame
                if (mb_x + 1 < mi_ctx->b_width)
                    ADD_PRED(preds[0], blocks[mb_i - mi_ctx->b_width + 1].mvs[dir][0], blocks[mb_i - mi_ctx->b_width + 1].mvs[dir][1]);
                //top-left mb in current frame
                else if (mb_x > 0)
                    ADD_PRED(preds[0], blocks[mb_i - mi_ctx->b_width - 1].mvs[dir][0], blocks[mb_i - mi_ctx->b_width - 1].mvs[dir][1]);
            }

            //median predictor
            if (preds[0].nb == 4) {
                me_ctx->pred_x = mid_pred(preds[0].mvs[1][0], preds[0].mvs[2][0], preds[0].mvs[3][0]);
                me_ctx->pred_y = mid_pred(preds[0].mvs[1][1], preds[0].mvs[2][1], preds[0].mvs[3][1]);
            } else if (preds[0].nb == 3) {
                me_ctx->pred_x = mid_pred(0, preds[0].mvs[1][0], preds[0].mvs[2][0]);
                me_ctx->pred_y = mid_pred(0, preds[0].mvs[1][1], preds[0].mvs[2][1]);
            } else if (preds[0].nb == 2) {
                me_ctx->pred_x = preds[0].mvs[1][0];
                me_ctx->pred_y = preds[0].mvs[1][1];
            } else {
                me_ctx->pred_x = 0;
                me_ctx->pred_y = 0;
            }

            ff_me_search_umh(me_ctx, x_mb, y_mb, mv);

            break;
    }

    block->mvs[dir][0] = mv[0] - x_mb;
    block->mvs[dir][1] = mv[1] - y_mb;
}