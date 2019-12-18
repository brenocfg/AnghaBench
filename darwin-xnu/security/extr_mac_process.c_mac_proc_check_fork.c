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
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_proc_check_enforce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_proc_enforce ; 
 int /*<<< orphan*/  proc_check_fork ; 

int
mac_proc_check_fork(proc_t curp)
{
	kauth_cred_t cred;
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_proc_enforce)
		return 0;
#endif
	if (!mac_proc_check_enforce(curp))
		return 0;

	cred = kauth_cred_proc_ref(curp);
	MAC_CHECK(proc_check_fork, cred, curp);
	kauth_cred_unref(&cred);

	return (error);
}