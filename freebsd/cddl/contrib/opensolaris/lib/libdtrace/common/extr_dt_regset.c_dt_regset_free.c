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
struct TYPE_3__ {int dr_size; int /*<<< orphan*/  dr_bitmap; } ;
typedef  TYPE_1__ dt_regset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLEAR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ BT_TEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void
dt_regset_free(dt_regset_t *drp, int reg)
{
	assert(reg >= 0 && reg < drp->dr_size);
	assert(BT_TEST(drp->dr_bitmap, reg) != 0);
	BT_CLEAR(drp->dr_bitmap, reg);
}