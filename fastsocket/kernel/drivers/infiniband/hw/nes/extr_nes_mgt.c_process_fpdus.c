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
struct nes_vnic {int dummy; } ;
struct nes_qp {int /*<<< orphan*/  pau_lock; scalar_t__ pau_busy; scalar_t__ pau_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  forward_fpdus (struct nes_vnic*,struct nes_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void process_fpdus(struct nes_vnic *nesvnic, struct nes_qp *nesqp)
{
	int again = 1;
	unsigned long flags;

	do {
		/* Ignore rc - if it failed, tcp retries will cause it to try again */
		forward_fpdus(nesvnic, nesqp);

		spin_lock_irqsave(&nesqp->pau_lock, flags);
		if (nesqp->pau_pending) {
			nesqp->pau_pending = 0;
		} else {
			nesqp->pau_busy = 0;
			again = 0;
		}

		spin_unlock_irqrestore(&nesqp->pau_lock, flags);
	} while (again);
}