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
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ disable_proc_mm ; 
 int /*<<< orphan*/  non_fatal (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int proc_mm ; 

__attribute__((used)) static inline void check_skas3_proc_mm(void)
{
	non_fatal("  - /proc/mm...");
	if (access("/proc/mm", W_OK) < 0)
		perror("not found");
	else if (disable_proc_mm)
		non_fatal("found but disabled on command line\n");
	else {
		proc_mm = 1;
		non_fatal("found\n");
	}
}