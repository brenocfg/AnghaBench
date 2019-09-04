#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_11__ {int mb_size; int search_param; int (* get_cost ) (TYPE_3__*,int,int,int,int) ;int pred_x; int pred_y; } ;
struct TYPE_10__ {int** mvs; int sb; struct TYPE_10__* subs; } ;
struct TYPE_9__ {TYPE_3__ me_ctx; } ;
typedef  TYPE_1__ MIContext ;
typedef  TYPE_2__ Block ;
typedef  TYPE_3__ AVMotionEstContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_mallocz_array (int,int) ; 
 int ff_me_search_ds (TYPE_3__*,int,int,int*) ; 
 int stub1 (TYPE_3__*,int,int,int,int) ; 

__attribute__((used)) static int var_size_bme(MIContext *mi_ctx, Block *block, int x_mb, int y_mb, int n)
{
    AVMotionEstContext *me_ctx = &mi_ctx->me_ctx;
    uint64_t cost_sb, cost_old;
    int mb_size = me_ctx->mb_size;
    int search_param = me_ctx->search_param;
    int mv_x, mv_y;
    int x, y;
    int ret;

    me_ctx->mb_size = 1 << n;
    cost_old = me_ctx->get_cost(me_ctx, x_mb, y_mb, x_mb + block->mvs[0][0], y_mb + block->mvs[0][1]);
    me_ctx->mb_size = mb_size;

    if (!cost_old) {
        block->sb = 0;
        return 0;
    }

    if (!block->subs) {
        block->subs = av_mallocz_array(4, sizeof(Block));
        if (!block->subs)
            return AVERROR(ENOMEM);
    }

    block->sb = 1;

    for (y = 0; y < 2; y++)
        for (x = 0; x < 2; x++) {
            Block *sb = &block->subs[x + y * 2];
            int mv[2] = {x_mb + block->mvs[0][0], y_mb + block->mvs[0][1]};

            me_ctx->mb_size = 1 << (n - 1);
            me_ctx->search_param = 2;
            me_ctx->pred_x = block->mvs[0][0];
            me_ctx->pred_y = block->mvs[0][1];

            cost_sb = ff_me_search_ds(&mi_ctx->me_ctx, x_mb + block->mvs[0][0], y_mb + block->mvs[0][1], mv);
            mv_x = mv[0] - x_mb;
            mv_y = mv[1] - y_mb;

            me_ctx->mb_size = mb_size;
            me_ctx->search_param = search_param;

            if (cost_sb < cost_old / 4) {
                sb->mvs[0][0] = mv_x;
                sb->mvs[0][1] = mv_y;

                if (n > 1) {
                    if (ret = var_size_bme(mi_ctx, sb, x_mb + (x << (n - 1)), y_mb + (y << (n - 1)), n - 1))
                        return ret;
                } else
                    sb->sb = 0;
            } else {
                block->sb = 0;
                return 0;
            }
        }

    return 0;
}