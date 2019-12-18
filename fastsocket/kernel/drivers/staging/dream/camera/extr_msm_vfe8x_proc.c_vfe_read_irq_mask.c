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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_irqenable {int dummy; } ;
typedef  int /*<<< orphan*/  rc ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_IRQ_MASK ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_irqenable*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vfe_irqenable vfe_read_irq_mask(void)
{
	/* unsigned long flags; */
	uint32_t *temp;
	struct vfe_irqenable rc;

	memset(&rc, 0, sizeof(rc));

	/* @todo This is causing issues, need further investigate */
	/* spin_lock_irqsave(&ctrl->io_lock, flags); */
	temp = (uint32_t *)(ctrl->vfebase + VFE_IRQ_MASK);

	rc = *((struct vfe_irqenable *)temp);
	/* spin_unlock_irqrestore(&ctrl->io_lock, flags); */

	return rc;
}