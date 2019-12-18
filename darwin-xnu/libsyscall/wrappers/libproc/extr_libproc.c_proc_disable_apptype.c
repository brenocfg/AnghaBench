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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_POLICY_ACTION_DISABLE ; 
 int /*<<< orphan*/  PROC_POLICY_APPTYPE ; 
#define  PROC_POLICY_OSX_APPTYPE_DASHCLIENT 129 
#define  PROC_POLICY_OSX_APPTYPE_TAL 128 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 

int 
proc_disable_apptype(pid_t pid, int apptype)
{
	switch (apptype) {
		case PROC_POLICY_OSX_APPTYPE_TAL:
		case PROC_POLICY_OSX_APPTYPE_DASHCLIENT:
			break;
		default:
			return(EINVAL);
	}

	if (__process_policy(PROC_POLICY_SCOPE_PROCESS, PROC_POLICY_ACTION_DISABLE, PROC_POLICY_APPTYPE, apptype, NULL, pid, (uint64_t)0) != -1)
		return(0);
	else
		return(errno);

}