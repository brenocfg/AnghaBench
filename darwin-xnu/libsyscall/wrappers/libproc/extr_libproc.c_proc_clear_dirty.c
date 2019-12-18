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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_DIRTYCONTROL_CLEAR ; 
 int /*<<< orphan*/  PROC_INFO_CALL_DIRTYCONTROL ; 
 int __proc_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errno ; 

int
proc_clear_dirty(pid_t pid, uint32_t flags)
{
	if (__proc_info(PROC_INFO_CALL_DIRTYCONTROL, pid, PROC_DIRTYCONTROL_CLEAR, flags, NULL, 0) == -1) {
		return errno;		
	}

	return 0;
}