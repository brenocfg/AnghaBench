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

/* Variables and functions */
 int /*<<< orphan*/  ktrace_active_mask ; 
 int ktrace_keep_ownership_on_reset ; 
 int /*<<< orphan*/  ktrace_reset_internal (int /*<<< orphan*/ ) ; 

void
ktrace_set_invalid_owning_pid(void)
{
	if (ktrace_keep_ownership_on_reset) {
		ktrace_keep_ownership_on_reset = false;
		ktrace_reset_internal(ktrace_active_mask);
	}
}