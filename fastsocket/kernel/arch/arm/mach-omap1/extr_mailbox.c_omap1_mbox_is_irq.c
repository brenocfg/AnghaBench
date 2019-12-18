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
struct omap_mbox {int dummy; } ;
typedef  scalar_t__ omap_mbox_type_t ;

/* Variables and functions */
 scalar_t__ IRQ_TX ; 

__attribute__((used)) static int
omap1_mbox_is_irq(struct omap_mbox *mbox, omap_mbox_type_t irq)
{
	if (irq == IRQ_TX)
		return 0;
	return 1;
}