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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ stripe_io_ref (struct stripe*) ; 

__attribute__((used)) static void stripe_io_get(struct stripe *stripe)
{
	if (atomic_inc_return(&stripe->io.pending) == 1)
		/* REMOVEME: statistics */
		atomic_inc(&stripe->sc->active_stripes);
	else
		BUG_ON(stripe_io_ref(stripe) < 0);
}