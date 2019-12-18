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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ EOVERFLOW ; 
 int /*<<< orphan*/  PROC_POLICY_ACTION_DROP ; 
 int /*<<< orphan*/  PROC_POLICY_BOOST ; 
 int /*<<< orphan*/  PROC_POLICY_IMP_IMPORTANT ; 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  important_boost_assertion_token ; 
 int /*<<< orphan*/  proc_importance_bad_assertion (char*) ; 

int
proc_importance_assertion_complete(uint64_t assertion_token)
{
	int rval = 0;

	if (assertion_token == 0)
		return (0);

	if (assertion_token == (uint64_t) &important_boost_assertion_token) {
		rval = __process_policy(PROC_POLICY_SCOPE_PROCESS,
								PROC_POLICY_ACTION_DROP,
								PROC_POLICY_BOOST,
								PROC_POLICY_IMP_IMPORTANT,
								NULL, getpid(), 0);		
		if (rval == 0) {
			return (0);
		} else if (errno == EOVERFLOW) {
			proc_importance_bad_assertion("Attempted to drop too many assertions");
			return (errno);
		} else {
			return (errno);
		}
	} else {
		proc_importance_bad_assertion("Attempted to drop assertion with invalid token");
		return (EIO);
	}
}