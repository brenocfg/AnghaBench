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
struct ub_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ub_scsi_dispatch (struct ub_dev*) ; 

__attribute__((used)) static void ub_scsi_action(unsigned long _dev)
{
	struct ub_dev *sc = (struct ub_dev *) _dev;
	unsigned long flags;

	spin_lock_irqsave(sc->lock, flags);
	ub_scsi_dispatch(sc);
	spin_unlock_irqrestore(sc->lock, flags);
}