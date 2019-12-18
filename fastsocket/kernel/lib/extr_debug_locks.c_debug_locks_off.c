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
 scalar_t__ __debug_locks_off () ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  debug_locks_silent ; 

int debug_locks_off(void)
{
	if (__debug_locks_off()) {
		if (!debug_locks_silent) {
			console_verbose();
			return 1;
		}
	}
	return 0;
}