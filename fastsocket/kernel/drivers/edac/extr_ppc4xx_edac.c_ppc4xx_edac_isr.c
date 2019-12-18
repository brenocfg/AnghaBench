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
struct mem_ctl_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ppc4xx_edac_check (struct mem_ctl_info*) ; 

__attribute__((used)) static irqreturn_t
ppc4xx_edac_isr(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;

	ppc4xx_edac_check(mci);

	return IRQ_HANDLED;
}