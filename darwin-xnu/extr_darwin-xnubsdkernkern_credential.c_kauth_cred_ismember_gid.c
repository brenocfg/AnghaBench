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
typedef  TYPE_1__* posix_cred_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {int cr_ngroups; scalar_t__* cr_groups; scalar_t__ cr_gmuid; } ;

/* Variables and functions */
 scalar_t__ KAUTH_UID_NONE ; 
 TYPE_1__* posix_cred_get (int /*<<< orphan*/ ) ; 

int
kauth_cred_ismember_gid(kauth_cred_t cred, gid_t gid, int *resultp)
{
	posix_cred_t pcred = posix_cred_get(cred);
	int i;

	/*
	 * Check the per-credential list of override groups.
	 *
	 * We can conditionalise this on cred->cr_gmuid == KAUTH_UID_NONE since
	 * the cache should be used for that case.
	 */
	for (i = 0; i < pcred->cr_ngroups; i++) {
		if (gid == pcred->cr_groups[i]) {
			*resultp = 1;
			return(0);
		}
	}

	/*
	 * If we don't have a UID for group membership checks, the in-cred list
	 * was authoritative and we can stop here.
	 */
	if (pcred->cr_gmuid == KAUTH_UID_NONE) {
		*resultp = 0;
		return(0);
	}
		
#if CONFIG_EXT_RESOLVER
	struct kauth_group_membership *gm;
	struct kauth_identity_extlookup el;
	int error;

	/*
	 * If the resolver hasn't checked in yet, we are early in the boot
	 * phase and the local group list is complete and authoritative.
	 */
	if (!kauth_resolver_registered) {
		*resultp = 0;
		return(0);
	}

	/* TODO: */
	/* XXX check supplementary groups */
	/* XXX check whiteout groups */
	/* XXX nesting of supplementary/whiteout groups? */

	/*
	 * Check the group cache.
	 */
	KAUTH_GROUPS_LOCK();
	TAILQ_FOREACH(gm, &kauth_groups, gm_link) {
		if ((gm->gm_uid == pcred->cr_gmuid) && (gm->gm_gid == gid) && !kauth_groups_expired(gm)) {
			kauth_groups_lru(gm);
			break;
		}
	}

	/* did we find a membership entry? */
	if (gm != NULL)
		*resultp = (gm->gm_flags & KAUTH_GROUP_ISMEMBER) ? 1 : 0;
	KAUTH_GROUPS_UNLOCK();

	/* if we did, we can return now */
	if (gm != NULL) {
		DTRACE_PROC2(kauth__group__cache__hit, int, pcred->cr_gmuid, int, gid);
		return(0);
	}

	/* nothing in the cache, need to go to userland */
	bzero(&el, sizeof(el));
	el.el_info_pid = current_proc()->p_pid;
	el.el_flags = KAUTH_EXTLOOKUP_VALID_UID | KAUTH_EXTLOOKUP_VALID_GID | KAUTH_EXTLOOKUP_WANT_MEMBERSHIP;
	el.el_uid = pcred->cr_gmuid;
	el.el_gid = gid;
	el.el_member_valid = 0;		/* XXX set by resolver? */

	DTRACE_PROC2(kauth__group__resolver__submitted, int, el.el_uid, int, el.el_gid);
	
	error = kauth_resolver_submit(&el, 0ULL);
	
	DTRACE_PROC2(kauth__group__resolver__returned, int, error, int, el.el_flags);
	
	if (error != 0)
		return(error);
	/* save the results from the lookup */
	kauth_groups_updatecache(&el);

	/* if we successfully ascertained membership, report */
	if (el.el_flags & KAUTH_EXTLOOKUP_VALID_MEMBERSHIP) {
		*resultp = (el.el_flags & KAUTH_EXTLOOKUP_ISMEMBER) ? 1 : 0;
		return(0);
	}

	return(ENOENT);
#else
	*resultp = 0;
	return(0);
#endif
}