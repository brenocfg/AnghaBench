#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ KTRACE_STATE_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ktrace_active_mask ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  ktrace_keep_ownership_on_reset ; 
 int /*<<< orphan*/  ktrace_reset_internal (int /*<<< orphan*/ ) ; 
 scalar_t__ ktrace_state ; 

void
ktrace_reset(uint32_t reset_mask)
{
	ktrace_assert_lock_held();

	if (ktrace_active_mask == 0) {
		if (!ktrace_keep_ownership_on_reset) {
			assert(ktrace_state == KTRACE_STATE_OFF);
		}
		return;
	}

	ktrace_reset_internal(reset_mask);
}