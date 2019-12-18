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
struct stripe {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_get (struct stripe*) ; 
 int /*<<< orphan*/  stripe_io_get (struct stripe*) ; 

__attribute__((used)) static void stripe_get_references(struct stripe *stripe, unsigned p)
{

	/*
	 * Another one to reference the stripe in
	 * order to protect vs. LRU list moves.
	 */
	io_get(RS(stripe->sc));	/* Global io references. */
	stripe_get(stripe);
	stripe_io_get(stripe);	/* One for each chunk io. */
}