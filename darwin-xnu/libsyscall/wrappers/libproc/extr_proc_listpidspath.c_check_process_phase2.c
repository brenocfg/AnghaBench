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
 int check_process_text (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_process_phase2(fdOpenInfoRef info, int pid)
{
	int	status;

	// check process text (memory)
	status = check_process_text(info, pid);
	if (status != 0) {
		// if error or match
		return status;
	}

	return 0;
}