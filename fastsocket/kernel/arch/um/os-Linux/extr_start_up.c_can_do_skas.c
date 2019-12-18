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
 int /*<<< orphan*/  check_skas3_proc_mm () ; 
 int /*<<< orphan*/  check_skas3_ptrace_faultinfo () ; 
 int /*<<< orphan*/  check_skas3_ptrace_ldt () ; 
 int /*<<< orphan*/  non_fatal (char*) ; 
 int /*<<< orphan*/  proc_mm ; 
 int /*<<< orphan*/  ptrace_faultinfo ; 
 int /*<<< orphan*/  ptrace_ldt ; 
 int skas_needs_stub ; 

void can_do_skas(void)
{
	non_fatal("Checking for the skas3 patch in the host:\n");

	check_skas3_proc_mm();
	check_skas3_ptrace_faultinfo();
	check_skas3_ptrace_ldt();

	if (!proc_mm || !ptrace_faultinfo || !ptrace_ldt)
		skas_needs_stub = 1;
}