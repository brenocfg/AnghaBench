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
 int /*<<< orphan*/  io_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_io_put (struct stripe*) ; 
 int /*<<< orphan*/  stripe_put (struct stripe*) ; 

__attribute__((used)) static void stripe_put_references(struct stripe *stripe)
{
	stripe_io_put(stripe);	/* One for each chunk io. */
	stripe_put(stripe);
	io_put(RS(stripe->sc));
}