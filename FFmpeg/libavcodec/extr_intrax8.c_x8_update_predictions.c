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
struct TYPE_3__ {int* prediction_table; int mb_x; int mb_y; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */

__attribute__((used)) static void x8_update_predictions(IntraX8Context *const w, const int orient,
                                  const int est_run)
{
    w->prediction_table[w->mb_x * 2 + (w->mb_y & 1)] = (est_run << 2) + 1 * (orient == 4) + 2 * (orient == 8);
/*
 * y = 2n + 0 -> // 0 2 4
 * y = 2n + 1 -> // 1 3 5
 */
}