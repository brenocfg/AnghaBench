#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  arcofitimer; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {TYPE_2__ dc; int /*<<< orphan*/  HW_Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ARCOFI_TIMER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
clear_arcofi(struct IsdnCardState *cs) {
	if (test_and_clear_bit(FLG_ARCOFI_TIMER, &cs->HW_Flags)) {
		del_timer(&cs->dc.isac.arcofitimer);
	}
}