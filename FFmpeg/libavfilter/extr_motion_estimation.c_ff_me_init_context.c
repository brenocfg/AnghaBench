#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int mb_size; int search_param; int x_min; int x_max; int y_min; int y_max; int /*<<< orphan*/ * get_cost; } ;
typedef  TYPE_1__ AVMotionEstContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_me_cmp_sad ; 

void ff_me_init_context(AVMotionEstContext *me_ctx, int mb_size, int search_param,
                        int width, int height, int x_min, int x_max, int y_min, int y_max)
{
    me_ctx->width = width;
    me_ctx->height = height;
    me_ctx->mb_size = mb_size;
    me_ctx->search_param = search_param;
    me_ctx->get_cost = &ff_me_cmp_sad;
    me_ctx->x_min = x_min;
    me_ctx->x_max = x_max;
    me_ctx->y_min = y_min;
    me_ctx->y_max = y_max;
}