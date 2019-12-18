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
struct stlbrd {int /*<<< orphan*/  (* isr ) (struct stlbrd*) ;int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlbrd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct stlbrd*) ; 

__attribute__((used)) static irqreturn_t stl_intr(int irq, void *dev_id)
{
	struct stlbrd *brdp = dev_id;

	pr_debug("stl_intr(brdp=%p,irq=%d)\n", brdp, brdp->irq);

	return IRQ_RETVAL((* brdp->isr)(brdp));
}