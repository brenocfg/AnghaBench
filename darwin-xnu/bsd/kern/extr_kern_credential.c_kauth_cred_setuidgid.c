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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  temp_cred ;
struct ucred {int /*<<< orphan*/  cr_label; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  struct ucred* kauth_cred_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_svuid; scalar_t__ cr_gid; scalar_t__ cr_rgid; scalar_t__ cr_svgid; int cr_flags; int cr_ngroups; void* cr_gmuid; } ;

/* Variables and functions */
 int CRF_NOMEMBERD ; 
 void* KAUTH_UID_NONE ; 
 int /*<<< orphan*/  NULLCRED_CHECK (struct ucred*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct ucred*,int) ; 
 scalar_t__ kauth_cred_change_egid (struct ucred*,scalar_t__) ; 
 struct ucred* kauth_cred_update (struct ucred*,struct ucred*,int /*<<< orphan*/ ) ; 
 TYPE_1__* posix_cred_get (struct ucred*) ; 

kauth_cred_t
kauth_cred_setuidgid(kauth_cred_t cred, uid_t uid, gid_t gid)
{
	struct ucred temp_cred;
	posix_cred_t temp_pcred = posix_cred_get(&temp_cred);
	posix_cred_t pcred;

	NULLCRED_CHECK(cred);

	pcred = posix_cred_get(cred);

	/*
	 * We don't need to do anything if the effective, real and saved
	 * user IDs are already the same as the user ID passed into us.
	 */
	if (pcred->cr_uid == uid && pcred->cr_ruid == uid && pcred->cr_svuid == uid &&
		pcred->cr_gid == gid && pcred->cr_rgid == gid && pcred->cr_svgid == gid) {
		/* no change needed */
		return(cred);
	}

	/*
	 * Look up in cred hash table to see if we have a matching credential
	 * with the new values.
	 */
	bzero(&temp_cred, sizeof(temp_cred));
	temp_pcred->cr_uid = uid;
	temp_pcred->cr_ruid = uid;
	temp_pcred->cr_svuid = uid;
	temp_pcred->cr_flags = pcred->cr_flags;
	/* inherit the opt-out of memberd */
	if (pcred->cr_flags & CRF_NOMEMBERD) {
		temp_pcred->cr_gmuid = KAUTH_UID_NONE;
		temp_pcred->cr_flags |= CRF_NOMEMBERD;
	} else {
		temp_pcred->cr_gmuid = uid;
		temp_pcred->cr_flags &= ~CRF_NOMEMBERD;
	}
	temp_pcred->cr_ngroups = 1;
	/* displacing a supplementary group opts us out of memberd */
	if (kauth_cred_change_egid(&temp_cred, gid)) {
		temp_pcred->cr_gmuid = KAUTH_UID_NONE;
		temp_pcred->cr_flags |= CRF_NOMEMBERD;
	}
	temp_pcred->cr_rgid = gid;
	temp_pcred->cr_svgid = gid;
#if CONFIG_MACF
	temp_cred.cr_label = cred->cr_label;
#endif

	return(kauth_cred_update(cred, &temp_cred, TRUE));
}