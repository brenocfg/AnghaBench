#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stripe_cache {int /*<<< orphan*/ * locks; struct list_head* lists; } ;
struct stripe {struct list_head* lists; struct stripe_cache* sc; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int LIST_ENDIO ; 
 int LOCK_ENDIO ; 
 int /*<<< orphan*/  RS (struct stripe_cache*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_do_raid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripe_endio_push(struct stripe *stripe)
{
	unsigned long flags;
	struct stripe_cache *sc = stripe->sc;
	struct list_head *stripe_list = stripe->lists + LIST_ENDIO,
			 *sc_list = sc->lists + LIST_ENDIO;
	spinlock_t *lock = sc->locks + LOCK_ENDIO;

	/* This runs in parallel with do_endios(). */
	spin_lock_irqsave(lock, flags);
	if (list_empty(stripe_list))
		list_add_tail(stripe_list, sc_list);
	spin_unlock_irqrestore(lock, flags);

	wake_do_raid(RS(sc)); /* Wake myself. */
}