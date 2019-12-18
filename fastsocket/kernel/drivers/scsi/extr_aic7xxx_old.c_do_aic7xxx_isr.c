#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aic7xxx_host {TYPE_1__* host; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_IN_ISR ; 
 int /*<<< orphan*/  INTSTAT ; 
 int INT_PEND ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  aic7xxx_done_cmds_complete (struct aic7xxx_host*) ; 
 int /*<<< orphan*/  aic7xxx_isr (void*) ; 
 int /*<<< orphan*/  aic7xxx_run_waiting_queues (struct aic7xxx_host*) ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t
do_aic7xxx_isr(int irq, void *dev_id)
{
  unsigned long cpu_flags;
  struct aic7xxx_host *p;
  
  p = dev_id;
  if(!p)
    return IRQ_NONE;
  spin_lock_irqsave(p->host->host_lock, cpu_flags);
  p->flags |= AHC_IN_ISR;
  do
  {
    aic7xxx_isr(dev_id);
  } while ( (aic_inb(p, INTSTAT) & INT_PEND) );
  aic7xxx_done_cmds_complete(p);
  aic7xxx_run_waiting_queues(p);
  p->flags &= ~AHC_IN_ISR;
  spin_unlock_irqrestore(p->host->host_lock, cpu_flags);

  return IRQ_HANDLED;
}