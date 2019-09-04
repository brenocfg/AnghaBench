#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atm_value_t ;
typedef  int /*<<< orphan*/  aid_t ;
struct TYPE_4__ {int sync; int reference_count; int /*<<< orphan*/  listener_lock; scalar_t__ listener_count; int /*<<< orphan*/  listeners; int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 TYPE_1__* ATM_VALUE_NULL ; 
 int /*<<< orphan*/  atm_lock_attr ; 
 int /*<<< orphan*/  atm_lock_grp ; 
 int /*<<< orphan*/  atm_value_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static atm_value_t
atm_value_alloc_init(aid_t aid)
{
	atm_value_t new_atm_value = ATM_VALUE_NULL;

	new_atm_value = (atm_value_t) zalloc(atm_value_zone);
	if (new_atm_value == ATM_VALUE_NULL)
		panic("Ran out of ATM values structure.\n\n");

	new_atm_value->aid = aid;
	queue_init(&new_atm_value->listeners);
	new_atm_value->sync = 1;
	new_atm_value->listener_count = 0;
	new_atm_value->reference_count = 1;
	lck_mtx_init(&new_atm_value->listener_lock, &atm_lock_grp, &atm_lock_attr);

#if DEVELOPMENT || DEBUG
	lck_mtx_lock(&atm_values_list_lock);
	queue_enter(&atm_values_list, new_atm_value, atm_value_t, value_elt);
	lck_mtx_unlock(&atm_values_list_lock);
#endif
	return new_atm_value;
}