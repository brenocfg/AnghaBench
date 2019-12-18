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
struct ehca_shca {int dummy; } ;
struct ehca_eq {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  ipz_queue; } ;

/* Variables and functions */
 void* ipz_eqit_eq_get_inc_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void *ehca_poll_eq(struct ehca_shca *shca, struct ehca_eq *eq)
{
	unsigned long flags;
	void *eqe;

	spin_lock_irqsave(&eq->spinlock, flags);
	eqe = ipz_eqit_eq_get_inc_valid(&eq->ipz_queue);
	spin_unlock_irqrestore(&eq->spinlock, flags);

	return eqe;
}