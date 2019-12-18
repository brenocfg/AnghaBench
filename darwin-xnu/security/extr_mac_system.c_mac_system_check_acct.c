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
struct vnode {int /*<<< orphan*/ * v_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_system_enforce ; 
 int /*<<< orphan*/  system_check_acct ; 

int
mac_system_check_acct(kauth_cred_t cred, struct vnode *vp)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_system_enforce)
		return (0);
#endif

	MAC_CHECK(system_check_acct, cred, vp,
	    vp != NULL ? vp->v_label : NULL);

	return (error);
}