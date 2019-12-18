#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {TYPE_1__* cred; int /*<<< orphan*/  filename; scalar_t__ cred_prepared; } ;
struct TYPE_2__ {int /*<<< orphan*/ * security; } ;

/* Variables and functions */
 int cap_bprm_set_creds (struct linux_binprm*) ; 
 int /*<<< orphan*/  tomoyo_load_policy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_policy_loaded ; 

__attribute__((used)) static int tomoyo_bprm_set_creds(struct linux_binprm *bprm)
{
	int rc;

	rc = cap_bprm_set_creds(bprm);
	if (rc)
		return rc;

	/*
	 * Do only if this function is called for the first time of an execve
	 * operation.
	 */
	if (bprm->cred_prepared)
		return 0;
	/*
	 * Load policy if /sbin/tomoyo-init exists and /sbin/init is requested
	 * for the first time.
	 */
	if (!tomoyo_policy_loaded)
		tomoyo_load_policy(bprm->filename);
	/*
	 * Tell tomoyo_bprm_check_security() is called for the first time of an
	 * execve operation.
	 */
	bprm->cred->security = NULL;
	return 0;
}