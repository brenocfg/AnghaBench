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
typedef  int /*<<< orphan*/  temp_cred ;
struct ucred {int dummy; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  struct ucred* kauth_cred_t ;
struct TYPE_3__ {scalar_t__ cr_ruid; scalar_t__ cr_uid; scalar_t__ cr_rgid; scalar_t__ cr_gid; scalar_t__ cr_gmuid; int /*<<< orphan*/  cr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_UNREF (struct ucred*) ; 
 int /*<<< orphan*/  CRF_NOMEMBERD ; 
 int /*<<< orphan*/  FREE_ZONE (struct ucred*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK () ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_UNLOCK () ; 
 scalar_t__ KAUTH_UID_NONE ; 
 int /*<<< orphan*/  M_CRED ; 
 int /*<<< orphan*/  bcopy (struct ucred*,struct ucred*,int) ; 
 int kauth_cred_add (struct ucred*) ; 
 scalar_t__ kauth_cred_change_egid (struct ucred*,scalar_t__) ; 
 struct ucred* kauth_cred_dup (struct ucred*) ; 
 struct ucred* kauth_cred_find (struct ucred*) ; 
 int /*<<< orphan*/  kauth_cred_ref (struct ucred*) ; 
 int /*<<< orphan*/  mac_cred_label_destroy (struct ucred*) ; 
 TYPE_1__* posix_cred_get (struct ucred*) ; 

kauth_cred_t
kauth_cred_copy_real(kauth_cred_t cred)
{
	kauth_cred_t newcred = NULL, found_cred;
	struct ucred temp_cred;
	posix_cred_t temp_pcred = posix_cred_get(&temp_cred);
	posix_cred_t pcred = posix_cred_get(cred);

	/* if the credential is already 'real', just take a reference */
	if ((pcred->cr_ruid == pcred->cr_uid) &&
	    (pcred->cr_rgid == pcred->cr_gid)) {
		kauth_cred_ref(cred);
		return(cred);
	}

	/*
	 * Look up in cred hash table to see if we have a matching credential
	 * with the new values.
	 */
	bcopy(cred, &temp_cred, sizeof(temp_cred));
	temp_pcred->cr_uid = pcred->cr_ruid;
	/* displacing a supplementary group opts us out of memberd */
	if (kauth_cred_change_egid(&temp_cred, pcred->cr_rgid)) {
		temp_pcred->cr_flags |= CRF_NOMEMBERD;
		temp_pcred->cr_gmuid = KAUTH_UID_NONE;
	}
	/*
	 * If the cred is not opted out, make sure we are using the r/euid
	 * for group checks
	 */
	if (temp_pcred->cr_gmuid != KAUTH_UID_NONE)
		temp_pcred->cr_gmuid = pcred->cr_ruid;

	for (;;) {
		int		err;
		
		KAUTH_CRED_HASH_LOCK();
		found_cred = kauth_cred_find(&temp_cred);
		if (found_cred == cred) {
			/* same cred so just bail */
			KAUTH_CRED_HASH_UNLOCK();
			return(cred); 
		}
		if (found_cred != NULL) {
			/*
			 * Found a match so we bump reference count on new
			 * one.  We leave the old one alone.
			 */
			kauth_cred_ref(found_cred);
			KAUTH_CRED_HASH_UNLOCK();
			return(found_cred);
		}
	
		/*
		 * Must allocate a new credential, copy in old credential
		 * data and update the real user and group IDs.
		 */
		newcred = kauth_cred_dup(&temp_cred);
		err = kauth_cred_add(newcred);
		KAUTH_CRED_HASH_UNLOCK();

		/* Retry if kauth_cred_add() fails */
		if (err == 0)
			break;
#if CONFIG_MACF
		mac_cred_label_destroy(newcred);
#endif
		AUDIT_SESSION_UNREF(newcred);

		FREE_ZONE(newcred, sizeof(*newcred), M_CRED);
		newcred = NULL;
	}
	
	return(newcred);
}