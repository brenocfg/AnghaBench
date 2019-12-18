#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct futex_pi_state {int /*<<< orphan*/  refcount; TYPE_1__* owner; int /*<<< orphan*/  pi_mutex; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct futex_pi_state* pi_state_cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (struct futex_pi_state*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_proxy_unlock (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pi_state(struct futex_pi_state *pi_state)
{
	if (!atomic_dec_and_test(&pi_state->refcount))
		return;

	/*
	 * If pi_state->owner is NULL, the owner is most probably dying
	 * and has cleaned up the pi_state already
	 */
	if (pi_state->owner) {
		spin_lock_irq(&pi_state->owner->pi_lock);
		list_del_init(&pi_state->list);
		spin_unlock_irq(&pi_state->owner->pi_lock);

		rt_mutex_proxy_unlock(&pi_state->pi_mutex, pi_state->owner);
	}

	if (current->pi_state_cache)
		kfree(pi_state);
	else {
		/*
		 * pi_state->list is already empty.
		 * clear pi_state->owner.
		 * refcount is at 0 - put it back to 1.
		 */
		pi_state->owner = NULL;
		atomic_set(&pi_state->refcount, 1);
		current->pi_state_cache = pi_state;
	}
}