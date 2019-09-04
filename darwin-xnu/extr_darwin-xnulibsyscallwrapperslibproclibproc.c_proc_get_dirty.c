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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_DIRTYCONTROL_GET ; 
 int /*<<< orphan*/  PROC_INFO_CALL_DIRTYCONTROL ; 
 int __proc_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errno ; 

int
proc_get_dirty(pid_t pid, uint32_t *flags)
{
	int retval;
	
	if (!flags) {
		return EINVAL;
	}
	
	retval = __proc_info(PROC_INFO_CALL_DIRTYCONTROL, pid, PROC_DIRTYCONTROL_GET, 0, NULL, 0);
	if (retval == -1) {
		return errno;		
	}
	
	*flags = retval;

	return 0;
}