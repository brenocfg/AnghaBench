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
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTITLEMENT_PERSONA_PROPAGATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOTaskHasEntitlement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_issuser (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
bank_task_is_propagate_entitled(task_t t)
{
	/* Return TRUE if root process */
	if (0 == kauth_cred_issuser(kauth_cred_get())) {
		/* If it's a non-root process, it needs to have the entitlement for secure originator propagation */
		boolean_t entitled = FALSE;
		entitled = IOTaskHasEntitlement(t, ENTITLEMENT_PERSONA_PROPAGATE);
		return entitled;
	} else {
		return TRUE;
	}
}