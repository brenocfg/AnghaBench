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
struct stripe_cache {scalar_t__ lists; } ;
struct stripe {int dummy; } ;
struct raid_set {struct stripe_cache sc; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ LIST_FLUSH ; 
 int /*<<< orphan*/  _do_endios (struct raid_set*,struct stripe*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,scalar_t__) ; 
 struct stripe* stripe_endio_pop (struct stripe_cache*) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 

__attribute__((used)) static void do_endios(struct raid_set *rs)
{
	struct stripe_cache *sc = &rs->sc;
	struct stripe *stripe;
	/* IO flush list for sorted requeued stripes. */
	struct list_head flush_list;

	INIT_LIST_HEAD(&flush_list);

	while ((stripe = stripe_endio_pop(sc))) {
		/* Avoid endio on stripes with newly io'ed chunks. */
		if (!stripe_io_ref(stripe))
			_do_endios(rs, stripe, &flush_list);
	}

	/*
	 * Insert any requeued stripes in the proper
	 * order at the beginning of the io (flush) list.
	 */
	list_splice(&flush_list, sc->lists + LIST_FLUSH);
}