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
struct stripe {int dummy; } ;
struct raid_set {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 struct stripe* stripe_io_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ stripe_rw (struct stripe*) ; 

__attribute__((used)) static int do_flush(struct raid_set *rs)
{
	int r = 0;
	struct stripe *stripe;

	while ((stripe = stripe_io_pop(&rs->sc)))
		r += stripe_rw(stripe); /* Read/write stripe. */

	return r;
}