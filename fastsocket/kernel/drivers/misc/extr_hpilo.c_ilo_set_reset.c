#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ilo_hwinfo {TYPE_1__** ccb_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_ccb; } ;

/* Variables and functions */
 int max_ccb ; 
 int /*<<< orphan*/  set_channel_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ilo_set_reset(struct ilo_hwinfo *hw)
{
	int slot;

	/*
	 * Mapped memory is zeroed on ilo reset, so set a per ccb flag
	 * to indicate that this ccb needs to be closed and reopened.
	 */
	for (slot = 0; slot < max_ccb; slot++) {
		if (!hw->ccb_alloc[slot])
			continue;
		set_channel_reset(&hw->ccb_alloc[slot]->driver_ccb);
	}
}