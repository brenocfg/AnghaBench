#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_cred_t ;
typedef  TYPE_2__* kauth_cred_t ;
struct TYPE_17__ {int /*<<< orphan*/  cr_audit; } ;
struct TYPE_16__ {int cr_flags; int cr_ngroups; int /*<<< orphan*/ * cr_groups; void* cr_gmuid; int /*<<< orphan*/  cr_svgid; int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/  cr_svuid; int /*<<< orphan*/  cr_ruid; void* cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_UNREF (TYPE_2__*) ; 
 int CRF_NOMEMBERD ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK () ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK_ASSERT () ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_UNLOCK () ; 
 void* KAUTH_UID_NONE ; 
 int /*<<< orphan*/  M_CRED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int kauth_cred_add (TYPE_2__*) ; 
 TYPE_2__* kauth_cred_alloc () ; 
 TYPE_2__* kauth_cred_find (TYPE_2__*) ; 
 int /*<<< orphan*/  kauth_cred_ismember_gid (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kauth_cred_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  mac_cred_label_destroy (TYPE_2__*) ; 
 TYPE_1__* posix_cred_get (TYPE_2__*) ; 

kauth_cred_t
kauth_cred_create(kauth_cred_t cred)
{
	kauth_cred_t 	found_cred, new_cred = NULL;
	posix_cred_t	pcred = posix_cred_get(cred);
	int is_member = 0;

	KAUTH_CRED_HASH_LOCK_ASSERT();

	if (pcred->cr_flags & CRF_NOMEMBERD) {
		pcred->cr_gmuid = KAUTH_UID_NONE;
	} else {
		/*
		 * If the template credential is not opting out of external
		 * group membership resolution, then we need to check that
		 * the UID we will be using is resolvable by the external
		 * resolver.  If it's not, then we opt it out anyway, since
		 * all future external resolution requests will be failing
		 * anyway, and potentially taking a long time to do it.  We
		 * use gid 0 because we always know it will exist and not
		 * trigger additional lookups. This is OK, because we end up
		 * precatching the information here as a result.
		 */
		if (!kauth_cred_ismember_gid(cred, 0, &is_member)) {
			/*
			 * It's a recognized value; we don't really care about
			 * the answer, so long as it's something the external
			 * resolver could have vended.
			 */
			pcred->cr_gmuid = pcred->cr_uid;
		} else {
			/*
			 * It's not something the external resolver could
			 * have vended, so we don't want to ask it more
			 * questions about the credential in the future. This
			 * speeds up future lookups, as long as the caller
			 * caches results; otherwise, it the same recurring
			 * cost.  Since most credentials are used multiple
			 * times, we still get some performance win from this.
			 */
			pcred->cr_gmuid = KAUTH_UID_NONE;
			pcred->cr_flags |= CRF_NOMEMBERD;
		}
	}

	/* Caller *must* specify at least the egid in cr_groups[0] */
	if (pcred->cr_ngroups < 1)
		return(NULL);
	
	for (;;) {
		KAUTH_CRED_HASH_LOCK();
		found_cred = kauth_cred_find(cred);
		if (found_cred != NULL) {
			/*
			 * Found an existing credential so we'll bump
			 * reference count and return
			 */
			kauth_cred_ref(found_cred);
			KAUTH_CRED_HASH_UNLOCK();
			return(found_cred);
		}
		KAUTH_CRED_HASH_UNLOCK();
	
		/*
		 * No existing credential found.  Create one and add it to
		 * our hash table.
		 */
		new_cred = kauth_cred_alloc();
		if (new_cred != NULL) {
			int		err;
			posix_cred_t	new_pcred = posix_cred_get(new_cred);
			new_pcred->cr_uid = pcred->cr_uid;
			new_pcred->cr_ruid = pcred->cr_ruid;
			new_pcred->cr_svuid = pcred->cr_svuid;
			new_pcred->cr_rgid = pcred->cr_rgid;
			new_pcred->cr_svgid = pcred->cr_svgid;
			new_pcred->cr_gmuid = pcred->cr_gmuid;
			new_pcred->cr_ngroups = pcred->cr_ngroups;	
			bcopy(&pcred->cr_groups[0], &new_pcred->cr_groups[0], sizeof(new_pcred->cr_groups));
#if CONFIG_AUDIT
			bcopy(&cred->cr_audit, &new_cred->cr_audit, 
			    sizeof(new_cred->cr_audit));
#endif
			new_pcred->cr_flags = pcred->cr_flags;
			
			KAUTH_CRED_HASH_LOCK();
			err = kauth_cred_add(new_cred);
			KAUTH_CRED_HASH_UNLOCK();
			
			/* Retry if kauth_cred_add returns non zero value */
			if (err == 0)
				break;
#if CONFIG_MACF
			mac_cred_label_destroy(new_cred);
#endif
			AUDIT_SESSION_UNREF(new_cred);

			FREE_ZONE(new_cred, sizeof(*new_cred), M_CRED);
			new_cred = NULL;
		}
	}

	return(new_cred);
}