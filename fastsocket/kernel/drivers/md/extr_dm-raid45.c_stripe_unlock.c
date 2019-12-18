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
struct stripe {int /*<<< orphan*/ * lock; int /*<<< orphan*/  sc; } ;
struct TYPE_4__ {TYPE_1__* locking; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripe_unlock(struct stripe *stripe)
{
	RS(stripe->sc)->locking->unlock(stripe->lock);
	stripe->lock = NULL;
}