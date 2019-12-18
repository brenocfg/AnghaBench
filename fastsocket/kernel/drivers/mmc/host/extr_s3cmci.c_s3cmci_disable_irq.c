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
struct s3cmci_host {int irq_disabled; int irq_state; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void s3cmci_disable_irq(struct s3cmci_host *host, bool transfer)
{
	unsigned long flags;

	local_irq_save(flags);

	//printk(KERN_DEBUG "%s: transfer %d\n", __func__, transfer);

	host->irq_disabled = transfer;

	if (transfer && host->irq_state) {
		host->irq_state = false;
		disable_irq(host->irq);
	}

	local_irq_restore(flags);
}