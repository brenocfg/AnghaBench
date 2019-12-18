#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kauth_cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {scalar_t__ cr_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_UNREF (TYPE_1__*) ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_LOCK () ; 
 int /*<<< orphan*/  KAUTH_CRED_HASH_UNLOCK () ; 
 int /*<<< orphan*/  M_CRED ; 
 TYPE_1__* NOCRED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kauth_cred_unref_hashlocked (TYPE_1__**) ; 
 int /*<<< orphan*/  mac_cred_label_destroy (TYPE_1__*) ; 

void
kauth_cred_unref(kauth_cred_t *credp)
{
	boolean_t destroy_it;

	KAUTH_CRED_HASH_LOCK();
	destroy_it = kauth_cred_unref_hashlocked(credp);
	KAUTH_CRED_HASH_UNLOCK();

	if (destroy_it == TRUE) {
		assert(*credp != NOCRED);
#if CONFIG_MACF
		mac_cred_label_destroy(*credp);
#endif
		AUDIT_SESSION_UNREF(*credp);

		(*credp)->cr_ref = 0;
		FREE_ZONE(*credp, sizeof(*(*credp)), M_CRED);
		*credp = NOCRED;
	}
}