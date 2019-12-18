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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int b8_stride; int mb_y; int mb_x; int mb_stride; scalar_t__*** last_mv; scalar_t__* ac_val; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

void ff_mpeg4_clean_buffers(MpegEncContext *s)
{
    int c_wrap, c_xy, l_wrap, l_xy;

    l_wrap = s->b8_stride;
    l_xy   = (2 * s->mb_y - 1) * l_wrap + s->mb_x * 2 - 1;
    c_wrap = s->mb_stride;
    c_xy   = (s->mb_y - 1) * c_wrap + s->mb_x - 1;

    /* clean AC */
    memset(s->ac_val[0] + l_xy, 0, (l_wrap * 2 + 1) * 16 * sizeof(int16_t));
    memset(s->ac_val[1] + c_xy, 0, (c_wrap     + 1) * 16 * sizeof(int16_t));
    memset(s->ac_val[2] + c_xy, 0, (c_wrap     + 1) * 16 * sizeof(int16_t));

    /* clean MV */
    // we can't clear the MVs as they might be needed by a B-frame
    s->last_mv[0][0][0] =
    s->last_mv[0][0][1] =
    s->last_mv[1][0][0] =
    s->last_mv[1][0][1] = 0;
}