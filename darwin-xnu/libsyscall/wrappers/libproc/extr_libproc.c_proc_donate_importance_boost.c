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
 int /*<<< orphan*/  PROC_POLICY_ACTION_ENABLE ; 
 int /*<<< orphan*/  PROC_POLICY_ACTION_SET ; 
 int /*<<< orphan*/  PROC_POLICY_APPTYPE ; 
 int /*<<< orphan*/  PROC_POLICY_BOOST ; 
 int /*<<< orphan*/  PROC_POLICY_IMP_DONATION ; 
 int /*<<< orphan*/  PROC_POLICY_IOS_DONATEIMP ; 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  getpid () ; 

int 
proc_donate_importance_boost()
{
	int rval;

#if TARGET_OS_EMBEDDED
	rval = __process_policy(PROC_POLICY_SCOPE_PROCESS,
							PROC_POLICY_ACTION_ENABLE,
							PROC_POLICY_APPTYPE,
							PROC_POLICY_IOS_DONATEIMP,
							NULL, getpid(), (uint64_t)0);
#else /* TARGET_OS_EMBEDDED */
	rval = __process_policy(PROC_POLICY_SCOPE_PROCESS,
							PROC_POLICY_ACTION_SET,
							PROC_POLICY_BOOST,
							PROC_POLICY_IMP_DONATION,
							NULL, getpid(), 0);
#endif /* TARGET_OS_EMBEDDED */

	if (rval == 0)
		return (0);
	else
		return (errno);
}