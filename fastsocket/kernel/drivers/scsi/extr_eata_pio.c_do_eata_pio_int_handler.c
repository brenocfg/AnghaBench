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
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  eata_pio_int_handler (int,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t do_eata_pio_int_handler(int irq, void *dev_id)
{
	unsigned long flags;
	struct Scsi_Host *dev = dev_id;
	irqreturn_t ret;

	spin_lock_irqsave(dev->host_lock, flags);
	ret = eata_pio_int_handler(irq, dev_id);
	spin_unlock_irqrestore(dev->host_lock, flags);
	return ret;
}