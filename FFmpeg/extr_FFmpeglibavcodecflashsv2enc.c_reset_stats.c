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
struct TYPE_3__ {double diff_blocks; int tot_blocks; double diff_lines; int tot_lines; int raw_size; int comp_size; int uncomp_size; } ;
typedef  TYPE_1__ FlashSV2Context ;

/* Variables and functions */

__attribute__((used)) static void reset_stats(FlashSV2Context * s)
{
#ifndef FLASHSV2_DUMB
    s->diff_blocks = 0.1;
    s->tot_blocks = 1;
    s->diff_lines = 0.1;
    s->tot_lines = 1;
    s->raw_size = s->comp_size = s->uncomp_size = 10;
#endif
}