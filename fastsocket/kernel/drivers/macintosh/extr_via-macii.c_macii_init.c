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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_FLG_LOCK ; 
 int /*<<< orphan*/  IRQ_MAC_ADB ; 
 int /*<<< orphan*/  idle ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int macii_init_via () ; 
 int /*<<< orphan*/  macii_interrupt ; 
 int /*<<< orphan*/  macii_state ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int macii_init(void)
{
	unsigned long flags;
	int err;
	
	local_irq_save(flags);
	
	err = macii_init_via();
	if (err) goto out;

	err = request_irq(IRQ_MAC_ADB, macii_interrupt, IRQ_FLG_LOCK, "ADB",
			  macii_interrupt);
	if (err) goto out;

	macii_state = idle;
out:
	local_irq_restore(flags);
	return err;
}