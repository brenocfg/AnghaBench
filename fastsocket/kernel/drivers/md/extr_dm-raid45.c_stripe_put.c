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
struct stripe {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int stripe_io_ref (struct stripe*) ; 
 scalar_t__ stripe_ref (struct stripe*) ; 
 int /*<<< orphan*/  stripe_unlock (struct stripe*) ; 

__attribute__((used)) static void stripe_put(struct stripe *stripe)
{
	if (atomic_dec_and_test(&stripe->cnt)) {
		BUG_ON(stripe_io_ref(stripe));
		stripe_unlock(stripe);
	} else
		BUG_ON(stripe_ref(stripe) < 0);
}