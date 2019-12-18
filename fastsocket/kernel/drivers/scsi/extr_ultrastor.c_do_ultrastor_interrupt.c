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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ultrastor_interrupt (void*) ; 

__attribute__((used)) static irqreturn_t do_ultrastor_interrupt(int irq, void *dev_id)
{
    unsigned long flags;
    struct Scsi_Host *dev = dev_id;
    
    spin_lock_irqsave(dev->host_lock, flags);
    ultrastor_interrupt(dev_id);
    spin_unlock_irqrestore(dev->host_lock, flags);
    return IRQ_HANDLED;
}