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
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred_unlock (int /*<<< orphan*/ ) ; 

kauth_cred_t
kauth_cred_proc_ref(proc_t procp)
{
	kauth_cred_t 	cred;
	
	proc_ucred_lock(procp);
	cred = proc_ucred(procp);
	kauth_cred_ref(cred);
	proc_ucred_unlock(procp);
	return(cred);
}