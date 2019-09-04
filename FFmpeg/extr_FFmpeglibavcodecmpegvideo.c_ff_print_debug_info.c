#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  quarter_sample; int /*<<< orphan*/  mb_stride; int /*<<< orphan*/  mb_height; int /*<<< orphan*/  mb_width; int /*<<< orphan*/  low_delay; int /*<<< orphan*/  mbskip_table; int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  motion_val; int /*<<< orphan*/  qscale_table; int /*<<< orphan*/  mb_type; } ;
typedef  TYPE_1__ Picture ;
typedef  TYPE_2__ MpegEncContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  ff_print_debug_info2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_print_debug_info(MpegEncContext *s, Picture *p, AVFrame *pict)
{
    ff_print_debug_info2(s->avctx, pict, s->mbskip_table, p->mb_type,
                         p->qscale_table, p->motion_val, &s->low_delay,
                         s->mb_width, s->mb_height, s->mb_stride, s->quarter_sample);
}