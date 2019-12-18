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
struct stripe_cache {int lists; } ;
struct stripe {struct list_head* lists; struct stripe_cache* sc; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int LIST_FLUSH ; 
 int /*<<< orphan*/  StripeReconstruct (struct stripe*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int) ; 
 scalar_t__ list_empty (struct list_head*) ; 

__attribute__((used)) static void stripe_flush_add(struct stripe *stripe)
{
	struct stripe_cache *sc = stripe->sc;
	struct list_head *lh = stripe->lists + LIST_FLUSH;

	if (!StripeReconstruct(stripe) && list_empty(lh))
		list_add_tail(lh, sc->lists + LIST_FLUSH);
}