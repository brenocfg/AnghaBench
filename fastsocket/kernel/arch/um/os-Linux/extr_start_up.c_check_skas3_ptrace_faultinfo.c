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
struct ptrace_faultinfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int /*<<< orphan*/  PTRACE_FAULTINFO ; 
 scalar_t__ disable_ptrace_faultinfo ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  non_fatal (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ptrace_faultinfo*) ; 
 int ptrace_faultinfo ; 
 int start_ptraced_child () ; 
 int /*<<< orphan*/  stop_ptraced_child (int,int,int) ; 

__attribute__((used)) static inline void check_skas3_ptrace_faultinfo(void)
{
	struct ptrace_faultinfo fi;
	int pid, n;

	non_fatal("  - PTRACE_FAULTINFO...");
	pid = start_ptraced_child();

	n = ptrace(PTRACE_FAULTINFO, pid, 0, &fi);
	if (n < 0) {
		if (errno == EIO)
			non_fatal("not found\n");
		else
			perror("not found");
	} else if (disable_ptrace_faultinfo)
		non_fatal("found but disabled on command line\n");
	else {
		ptrace_faultinfo = 1;
		non_fatal("found\n");
	}

	stop_ptraced_child(pid, 1, 1);
}