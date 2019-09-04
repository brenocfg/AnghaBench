#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atm_value_t ;
struct TYPE_6__ {scalar_t__ reference_count; int /*<<< orphan*/  listener_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atm_listener_delete_all (TYPE_1__*) ; 
 int /*<<< orphan*/  atm_lock_grp ; 
 scalar_t__ atm_value_release_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  atm_value_zone ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
atm_value_dealloc(atm_value_t atm_value)
{
	if (0 < atm_value_release_internal(atm_value)) {
		return;
	}

	assert(atm_value->reference_count == 0);

	/* Free up the atm value and also remove all the listeners. */
	atm_listener_delete_all(atm_value);

	lck_mtx_destroy(&atm_value->listener_lock, &atm_lock_grp);

#if DEVELOPMENT || DEBUG
	lck_mtx_lock(&atm_values_list_lock);
	queue_remove(&atm_values_list, atm_value, atm_value_t, value_elt);
	lck_mtx_unlock(&atm_values_list_lock);
#endif
	zfree(atm_value_zone, atm_value);
	return;
}