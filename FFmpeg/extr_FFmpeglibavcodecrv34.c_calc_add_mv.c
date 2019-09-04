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
struct TYPE_3__ {int mv_weight2; int mv_weight1; } ;
typedef  int SUINT ;
typedef  TYPE_1__ RV34DecContext ;

/* Variables and functions */

__attribute__((used)) static int calc_add_mv(RV34DecContext *r, int dir, int val)
{
    int mul = dir ? -r->mv_weight2 : r->mv_weight1;

    return (int)(val * (SUINT)mul + 0x2000) >> 14;
}