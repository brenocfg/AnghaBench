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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WORK_UPDATE_OTG ; 
 int /*<<< orphan*/  isp1301_defer_work (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t isp1301_irq(int irq, void *isp)
{
	isp1301_defer_work(isp, WORK_UPDATE_OTG);
	return IRQ_HANDLED;
}