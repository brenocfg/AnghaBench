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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  absolutetime_to_nanoseconds (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
panic_display_uptime(void) {
	uint64_t	uptime;
	absolutetime_to_nanoseconds(mach_absolute_time(), &uptime);

	paniclog_append_noflush("\nSystem uptime in nanoseconds: %llu\n", uptime);
}