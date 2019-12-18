#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  TYPE_1__* posix_cred_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {int cr_flags; int /*<<< orphan*/  cr_groups; int /*<<< orphan*/  cr_ngroups; } ;

/* Variables and functions */
 int CRF_NOMEMBERD ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int NGROUPS ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int kauth_cred_uid2groups (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ kauth_external_supplementary_groups_supported ; 
 scalar_t__ kauth_identitysvc_has_registered ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* posix_cred_get (int /*<<< orphan*/ ) ; 

int
kauth_cred_getgroups(kauth_cred_t cred, gid_t *grouplist, int *countp)
{
	int limit = NGROUPS;
	posix_cred_t pcred;
	
	pcred = posix_cred_get(cred);

#if CONFIG_EXT_RESOLVER  
	/*
	 * If we've not opted out of using the resolver, then convert the cred to a list
	 * of supplemental groups. We do this only if there has been a resolver to talk to,
	 * since we may be too early in boot, or in an environment that isn't using DS.
	 */
	if (kauth_identitysvc_has_registered && kauth_external_supplementary_groups_supported && (pcred->cr_flags & CRF_NOMEMBERD) == 0) {		
		uid_t uid = kauth_cred_getuid(cred);
		int err;
		
		err = kauth_cred_uid2groups(&uid, grouplist, countp);
		if (!err)
			return 0;

		/* On error just fall through */
		KAUTH_DEBUG("kauth_cred_getgroups failed %d\n", err);
	}
#endif /* CONFIG_EXT_RESOLVER */

	/*
	 * If they just want a copy of the groups list, they may not care
	 * about the actual count.  If they specify an input count, however,
	 * treat it as an indicator of the buffer size available in grouplist,
	 * and limit the returned list to that size.
	 */
	if (countp) {
		limit = MIN(*countp, pcred->cr_ngroups);
		*countp = limit;
	}

	memcpy(grouplist, pcred->cr_groups, sizeof(gid_t) * limit);

	return 0;
}