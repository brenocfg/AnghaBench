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
struct TYPE_3__ {int /*<<< orphan*/  pending; } ;
struct stripe {TYPE_2__* sc; TYPE_1__ io; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_stripes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RS (TYPE_2__*) ; 
 int /*<<< orphan*/  StripeRecover (struct stripe*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stripe_endio_push (struct stripe*) ; 
 scalar_t__ stripe_io_ref (struct stripe*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_do_raid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripe_io_put(struct stripe *stripe)
{
	if (atomic_dec_and_test(&stripe->io.pending)) {
		if (unlikely(StripeRecover(stripe)))
			/* Don't put recovery stripe on endio list. */
			wake_do_raid(RS(stripe->sc));
		else
			/* Add regular stripe to endio list and wake daemon. */
			stripe_endio_push(stripe);

		/* REMOVEME: statistics */
		atomic_dec(&stripe->sc->active_stripes);
	} else
		BUG_ON(stripe_io_ref(stripe) < 0);
}