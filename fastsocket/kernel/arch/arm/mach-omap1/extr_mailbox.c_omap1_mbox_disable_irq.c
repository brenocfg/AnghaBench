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
struct omap_mbox {int /*<<< orphan*/  irq; } ;
typedef  scalar_t__ omap_mbox_type_t ;

/* Variables and functions */
 scalar_t__ IRQ_RX ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
omap1_mbox_disable_irq(struct omap_mbox *mbox, omap_mbox_type_t irq)
{
	if (irq == IRQ_RX)
		disable_irq(mbox->irq);
}