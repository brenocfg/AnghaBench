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
struct hw {int /*<<< orphan*/ * irq_callback; } ;
struct ct_timer {TYPE_2__* ops; TYPE_1__* atc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_global ) (struct ct_timer*) ;} ;
struct TYPE_3__ {struct hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ct_timer*) ; 
 int /*<<< orphan*/  stub1 (struct ct_timer*) ; 

void ct_timer_free(struct ct_timer *atimer)
{
	struct hw *hw = atimer->atc->hw;
	hw->irq_callback = NULL;
	if (atimer->ops->free_global)
		atimer->ops->free_global(atimer);
	kfree(atimer);
}