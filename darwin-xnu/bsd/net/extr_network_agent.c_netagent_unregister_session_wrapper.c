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
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_2__ {int netagent_flags; int /*<<< orphan*/  netagent_uuid; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;
struct netagent_session {struct netagent_wrapper* wrapper; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KEV_NETAGENT_UNREGISTERED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct netagent_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int NETAGENT_FLAG_ACTIVE ; 
 int TRUE ; 
 int /*<<< orphan*/  ifnet_clear_netagent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_chain ; 
 scalar_t__ netagent_active_count ; 
 int /*<<< orphan*/  netagent_free_wrapper (struct netagent_wrapper*) ; 
 int /*<<< orphan*/  netagent_lock ; 
 int /*<<< orphan*/  netagent_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netagent_registered_count ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netagent_unregister_session_wrapper(struct netagent_session *session)
{
	bool unregistered = FALSE;
	uuid_t unregistered_uuid;
	struct netagent_wrapper *wrapper = NULL;
	lck_rw_lock_exclusive(&netagent_lock);
	if (session != NULL) {
		wrapper = session->wrapper;
		if (wrapper != NULL) {
			if (netagent_registered_count > 0) {
				netagent_registered_count--;
			}
			if ((session->wrapper->netagent.netagent_flags & NETAGENT_FLAG_ACTIVE) &&
				netagent_active_count > 0) {
				netagent_active_count--;
			}

			LIST_REMOVE(wrapper, master_chain);

			unregistered = TRUE;
			uuid_copy(unregistered_uuid, session->wrapper->netagent.netagent_uuid);

			netagent_free_wrapper(session->wrapper);
			session->wrapper = NULL;
			NETAGENTLOG0(LOG_DEBUG, "Unregistered agent");
		}
	}
	lck_rw_done(&netagent_lock);

	if (unregistered) {
		ifnet_clear_netagent(unregistered_uuid);
		netagent_post_event(unregistered_uuid, KEV_NETAGENT_UNREGISTERED, TRUE);
	}
}