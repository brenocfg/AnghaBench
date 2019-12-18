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
struct s3cmci_host {int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dbg (struct s3cmci_host*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbg_irq ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static irqreturn_t s3cmci_irq_cd(int irq, void *dev_id)
{
	struct s3cmci_host *host = (struct s3cmci_host *)dev_id;

	dbg(host, dbg_irq, "card detect\n");

	mmc_detect_change(host->mmc, msecs_to_jiffies(500));

	return IRQ_HANDLED;
}