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
typedef  int /*<<< orphan*/  fdOpenInfoRef ;

/* Variables and functions */
 int check_process_fds (int /*<<< orphan*/ ,int) ; 
 int check_process_threads (int /*<<< orphan*/ ,int) ; 
 int check_process_vnodes (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_process_phase1(fdOpenInfoRef info, int pid)
{
	int	status;

	// check root and current working directory
	status = check_process_vnodes(info, pid);
	if (status != 0) {
		// if error or match
		return status;
	}

	// check open file descriptors
	status = check_process_fds(info, pid);
	if (status != 0) {
		// if error or match
		return status;
	}

	// check per-thread working directories
	status = check_process_threads(info, pid);
	if (status != 0) {
		// if error or match
		return status;
	}

	return 0;
}