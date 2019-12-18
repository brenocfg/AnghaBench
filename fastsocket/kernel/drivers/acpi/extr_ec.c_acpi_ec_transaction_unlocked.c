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
struct transaction {scalar_t__ command; } ;
struct acpi_ec {int /*<<< orphan*/  curr_lock; struct transaction* curr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ACPI_EC_COMMAND_QUERY ; 
 int /*<<< orphan*/  ACPI_EC_MSI_UDELAY ; 
 scalar_t__ EC_FLAGS_MSI ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ec_poll (struct acpi_ec*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_transaction (struct acpi_ec*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_ec_transaction_unlocked(struct acpi_ec *ec,
					struct transaction *t)
{
	unsigned long tmp;
	int ret = 0;
	if (EC_FLAGS_MSI)
		udelay(ACPI_EC_MSI_UDELAY);
	/* start transaction */
	spin_lock_irqsave(&ec->curr_lock, tmp);
	/* following two actions should be kept atomic */
	ec->curr = t;
	start_transaction(ec);
	if (ec->curr->command == ACPI_EC_COMMAND_QUERY)
		clear_bit(EC_FLAGS_QUERY_PENDING, &ec->flags);
	spin_unlock_irqrestore(&ec->curr_lock, tmp);
	ret = ec_poll(ec);
	spin_lock_irqsave(&ec->curr_lock, tmp);
	ec->curr = NULL;
	spin_unlock_irqrestore(&ec->curr_lock, tmp);
	return ret;
}