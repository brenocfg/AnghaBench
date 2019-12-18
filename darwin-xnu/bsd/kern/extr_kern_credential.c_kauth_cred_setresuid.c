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
struct ucred {int dummy; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  struct ucred* kauth_cred_t ;
struct TYPE_3__ {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_svuid; scalar_t__ cr_gmuid; int /*<<< orphan*/  cr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRF_NOMEMBERD ; 
 scalar_t__ KAUTH_UID_NONE ; 
 int /*<<< orphan*/  NULLCRED_CHECK (struct ucred*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (struct ucred*,struct ucred*,int) ; 
 struct ucred* kauth_cred_update (struct ucred*,struct ucred*,int /*<<< orphan*/ ) ; 
 TYPE_1__* posix_cred_get (struct ucred*) ; 

kauth_cred_t
kauth_cred_setresuid(kauth_cred_t cred, uid_t ruid, uid_t euid, uid_t svuid, uid_t gmuid)
{
	struct ucred temp_cred;
	posix_cred_t temp_pcred = posix_cred_get(&temp_cred);
	posix_cred_t pcred = posix_cred_get(cred);

	NULLCRED_CHECK(cred);

	/*
	 * We don't need to do anything if the UIDs we are changing are
	 * already the same as the UIDs passed in
	 */
	if ((euid == KAUTH_UID_NONE || pcred->cr_uid == euid) &&
	    (ruid == KAUTH_UID_NONE || pcred->cr_ruid == ruid) &&
	    (svuid == KAUTH_UID_NONE || pcred->cr_svuid == svuid) &&
	    (pcred->cr_gmuid == gmuid)) {
		/* no change needed */
		return(cred);
	}

	/*
	 * Look up in cred hash table to see if we have a matching credential
	 * with the new values; this is done by calling kauth_cred_update().
	 */
	bcopy(cred, &temp_cred, sizeof(temp_cred));
	if (euid != KAUTH_UID_NONE) {
		temp_pcred->cr_uid = euid;
	}
	if (ruid != KAUTH_UID_NONE) {
		temp_pcred->cr_ruid = ruid;
	}
	if (svuid != KAUTH_UID_NONE) {
		temp_pcred->cr_svuid = svuid;
	}

	/*
	 * If we are setting the gmuid to KAUTH_UID_NONE, then we want to
	 * opt out of participation in external group resolution, unless we
	 * unless we explicitly opt back in later.
	 */
	if ((temp_pcred->cr_gmuid = gmuid) == KAUTH_UID_NONE) {
		temp_pcred->cr_flags |= CRF_NOMEMBERD;
	}

	return(kauth_cred_update(cred, &temp_cred, TRUE));
}