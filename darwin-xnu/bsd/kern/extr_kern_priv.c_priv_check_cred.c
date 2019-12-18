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
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EPERM ; 
 int PRIVCHECK_DEFAULT_UNPRIVILEGED_FLAG ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int mac_priv_check (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mac_priv_grant (int /*<<< orphan*/ ,int) ; 

int
priv_check_cred(kauth_cred_t cred, int priv, int flags)
{
#if !CONFIG_MACF
#pragma unused(priv)
#endif
	int error;

	/*
	 * We first evaluate policies that may deny the granting of
	 * privilege unilaterally.
	 */
#if CONFIG_MACF
	error = mac_priv_check(cred, priv);
	if (error)
		goto out;
#endif

	/* Only grant all privileges to root if DEFAULT_UNPRIVELEGED flag is NOT set. */
	if (!(flags & PRIVCHECK_DEFAULT_UNPRIVILEGED_FLAG)) {
		/*
		* Having determined if privilege is restricted by various policies,
		* now determine if privilege is granted.	At this point, any policy
		* may grant privilege.	For now, we allow short-circuit boolean
		* evaluation, so may not call all policies.	 Perhaps we should.
		*/
		if (kauth_cred_getuid(cred) == 0) {
			error = 0;
			goto out;
		}
	}

	/*
	 * Now check with MAC, if enabled, to see if a policy module grants
	 * privilege.
	 */
#if CONFIG_MACF
	if (mac_priv_grant(cred, priv) == 0) {
		error = 0;
		goto out;
	}
#endif

	/*
	 * The default is deny, so if no policies have granted it, reject
	 * with a privilege error here.
	 */
	error = EPERM;
out:
	return (error);
}