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
typedef  scalar_t__ uid_t ;
struct socket {int so_flags; int /*<<< orphan*/ * so_cred; int /*<<< orphan*/  e_pid; } ;
typedef  scalar_t__ proc_t ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ PROC_NULL ; 
 int SOF_DELEGATED ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kauth_cred_proc_ref (scalar_t__) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 
 int priv_check_cred (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 

int
soopt_cred_check(struct socket *so, int priv, boolean_t allow_root)
{
	kauth_cred_t cred =  NULL;
	proc_t ep = PROC_NULL;
	uid_t uid;
	int error = 0;

	if (so->so_flags & SOF_DELEGATED) {
		ep = proc_find(so->e_pid);
		if (ep)
			cred = kauth_cred_proc_ref(ep);
	}

	uid = kauth_cred_getuid(cred ? cred : so->so_cred);

	/* uid is 0 for root */
	if (uid != 0 || !allow_root)
		error = priv_check_cred(cred ? cred : so->so_cred, priv, 0);
	if (cred)
		kauth_cred_unref(&cred);
	if (ep != PROC_NULL)
		proc_rele(ep);

	return (error);
}