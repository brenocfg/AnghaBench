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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int linesize; int mb_size; scalar_t__* data_cur; scalar_t__* data_ref; } ;
typedef  TYPE_1__ AVMotionEstContext ;

/* Variables and functions */
 scalar_t__ FFABS (scalar_t__) ; 

uint64_t ff_me_cmp_sad(AVMotionEstContext *me_ctx, int x_mb, int y_mb, int x_mv, int y_mv)
{
    const int linesize = me_ctx->linesize;
    uint8_t *data_ref = me_ctx->data_ref;
    uint8_t *data_cur = me_ctx->data_cur;
    uint64_t sad = 0;
    int i, j;

    data_ref += y_mv * linesize;
    data_cur += y_mb * linesize;

    for (j = 0; j < me_ctx->mb_size; j++)
        for (i = 0; i < me_ctx->mb_size; i++)
            sad += FFABS(data_ref[x_mv + i + j * linesize] - data_cur[x_mb + i + j * linesize]);

    return sad;
}