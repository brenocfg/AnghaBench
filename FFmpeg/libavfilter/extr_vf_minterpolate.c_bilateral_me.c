#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__** mvs; scalar_t__ sb; scalar_t__ cid; } ;
struct TYPE_6__ {int b_height; int b_width; TYPE_2__* int_blocks; } ;
typedef  TYPE_1__ MIContext ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  search_mv (TYPE_1__*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bilateral_me(MIContext *mi_ctx)
{
    Block *block;
    int mb_x, mb_y;

    for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
        for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
            block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];

            block->cid = 0;
            block->sb = 0;

            block->mvs[0][0] = 0;
            block->mvs[0][1] = 0;
        }

    for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
        for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++)
            search_mv(mi_ctx, mi_ctx->int_blocks, mb_x, mb_y, 0);
}