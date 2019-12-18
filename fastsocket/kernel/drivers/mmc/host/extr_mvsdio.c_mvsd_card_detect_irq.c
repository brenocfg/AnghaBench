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
struct mvsd_host {int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static irqreturn_t mvsd_card_detect_irq(int irq, void *dev)
{
	struct mvsd_host *host = dev;
	mmc_detect_change(host->mmc, msecs_to_jiffies(100));
	return IRQ_HANDLED;
}