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
struct TYPE_3__ {unsigned int vsub_max; unsigned int hsub_max; } ;
typedef  TYPE_1__ FFDrawContext ;

/* Variables and functions */

int ff_draw_round_to_sub(FFDrawContext *draw, int sub_dir, int round_dir,
                         int value)
{
    unsigned shift = sub_dir ? draw->vsub_max : draw->hsub_max;

    if (!shift)
        return value;
    if (round_dir >= 0)
        value += round_dir ? (1 << shift) - 1 : 1 << (shift - 1);
    return (value >> shift) << shift;
}