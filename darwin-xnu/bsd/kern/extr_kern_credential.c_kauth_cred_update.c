#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kauth_cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_19__ {scalar_t__ cr_ref; int /*<<< orphan*/  cr_audit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_UNREF (TYPE_1__*) ; 
 int /*<<< orphan*/  DEBUG_CRED_CHANGE (char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK () ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_UNLOCK () ; 
 int /*<<< orphan*/  M_CRED ; 
 TYPE_1__* NOCRED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int kauth_cred_add (TYPE_1__*) ; 
 TYPE_1__* kauth_cred_dup (TYPE_1__*) ; 
 TYPE_1__* kauth_cred_find (TYPE_1__*) ; 
 int /*<<< orphan*/  kauth_cred_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (TYPE_1__**) ; 
 scalar_t__ kauth_cred_unref_hashlocked (TYPE_1__**) ; 
 int /*<<< orphan*/  mac_cred_label_destroy (TYPE_1__*) ; 

__attribute__((used)) static kauth_cred_t
kauth_cred_update(kauth_cred_t old_cred, kauth_cred_t model_cred,
	boolean_t retain_auditinfo)
{	
	kauth_cred_t found_cred, new_cred = NULL;
	
	/*
	 * Make sure we carry the auditinfo forward to the new credential
	 * unless we are actually updating the auditinfo.
	 */
	if (retain_auditinfo) {
		bcopy(&old_cred->cr_audit, &model_cred->cr_audit, 
		    sizeof(model_cred->cr_audit));
	}
	
	for (;;) {
		int		err;

		KAUTH_CRED_HASH_LOCK();
		found_cred = kauth_cred_find(model_cred);
		if (found_cred == old_cred) {
			/* same cred so just bail */
			KAUTH_CRED_HASH_UNLOCK();
			return(old_cred); 
		}
		if (found_cred != NULL) {
			boolean_t destroy_it;

			DEBUG_CRED_CHANGE("kauth_cred_update(cache hit): %p -> %p\n", old_cred, found_cred);
			/*
			 * Found a match so we bump reference count on new
			 * one and decrement reference count on the old one.
			 */
			kauth_cred_ref(found_cred);
			destroy_it = kauth_cred_unref_hashlocked(&old_cred);
			KAUTH_CRED_HASH_UNLOCK();
			if (destroy_it == TRUE) {
				assert(old_cred != NOCRED);
#if CONFIG_MACF
				mac_cred_label_destroy(old_cred);
#endif
				AUDIT_SESSION_UNREF(old_cred);

				old_cred->cr_ref = 0;
				FREE_ZONE(old_cred, sizeof(*old_cred), M_CRED);
				old_cred = NOCRED;

			}
			return(found_cred);
		}

		/*
		 * Must allocate a new credential using the model.  also
		 * adds the new credential to the credential hash table.
		 */
		new_cred = kauth_cred_dup(model_cred);
		err = kauth_cred_add(new_cred);
		KAUTH_CRED_HASH_UNLOCK();

		/* retry if kauth_cred_add returns non zero value */
		if (err == 0)
			break;
#if CONFIG_MACF
		mac_cred_label_destroy(new_cred);
#endif
		AUDIT_SESSION_UNREF(new_cred);

		FREE_ZONE(new_cred, sizeof(*new_cred), M_CRED);
		new_cred = NULL;
	}

	DEBUG_CRED_CHANGE("kauth_cred_update(cache miss): %p -> %p\n", old_cred, new_cred);
	kauth_cred_unref(&old_cred);
	return(new_cred);
}