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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_proc_check_enforce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vm_enforce ; 
 int /*<<< orphan*/  proc_check_map_anon ; 

int
mac_proc_check_map_anon(proc_t proc, user_addr_t u_addr,
    user_size_t u_size, int prot, int flags, int *maxprot)
{
	kauth_cred_t cred;
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_vm_enforce)
		return 0;
#endif
	if (!mac_proc_check_enforce(proc))
		return (0);

	cred = kauth_cred_proc_ref(proc);
	MAC_CHECK(proc_check_map_anon, proc, cred, u_addr, u_size, prot, flags, maxprot);
	kauth_cred_unref(&cred);

	return (error);
}