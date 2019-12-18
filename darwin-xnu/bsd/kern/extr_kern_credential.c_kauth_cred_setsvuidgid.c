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
typedef  int /*<<< orphan*/  temp_cred ;
struct ucred {int /*<<< orphan*/  cr_svgid; int /*<<< orphan*/  cr_svuid; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  struct ucred* kauth_cred_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {scalar_t__ cr_svgid; int /*<<< orphan*/  cr_svuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CRED_CHANGE (char*) ; 
 int /*<<< orphan*/  DEBUG_CRED_ENTER (char*,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NULLCRED_CHECK (struct ucred*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (struct ucred*,struct ucred*,int) ; 
 struct ucred* kauth_cred_update (struct ucred*,struct ucred*,int /*<<< orphan*/ ) ; 
 TYPE_1__* posix_cred_get (struct ucred*) ; 

kauth_cred_t
kauth_cred_setsvuidgid(kauth_cred_t cred, uid_t uid, gid_t gid)
{
	struct ucred temp_cred;
	posix_cred_t temp_pcred = posix_cred_get(&temp_cred);
	posix_cred_t pcred;

	NULLCRED_CHECK(cred);

	pcred = posix_cred_get(cred);

	DEBUG_CRED_ENTER("kauth_cred_setsvuidgid: %p u%d->%d g%d->%d\n", cred, cred->cr_svuid, uid, cred->cr_svgid, gid);

	/*
	 * We don't need to do anything if the effective, real and saved
	 * uids are already the same as the uid provided.  This check is
	 * likely insufficient.
	 */
	if (pcred->cr_svuid == uid && pcred->cr_svgid == gid) {
		/* no change needed */
		return(cred);
	}
	DEBUG_CRED_CHANGE("kauth_cred_setsvuidgid: cred change\n");

	/* look up in cred hash table to see if we have a matching credential
	 * with new values.
	 */
	bcopy(cred, &temp_cred, sizeof(temp_cred));
	temp_pcred->cr_svuid = uid;
	temp_pcred->cr_svgid = gid;

	return(kauth_cred_update(cred, &temp_cred, TRUE));
}