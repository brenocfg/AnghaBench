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
typedef  scalar_t__ u8 ;
struct transaction {int rlen; int /*<<< orphan*/  wlen; scalar_t__* rdata; int /*<<< orphan*/ * wdata; int /*<<< orphan*/  command; } ;
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EC_COMMAND_QUERY ; 
 int EINVAL ; 
 int ENODATA ; 
 int acpi_ec_transaction_unlocked (struct acpi_ec*,struct transaction*) ; 

__attribute__((used)) static int acpi_ec_query_unlocked(struct acpi_ec *ec, u8 * data)
{
	int result;
	u8 d;
	struct transaction t = {.command = ACPI_EC_COMMAND_QUERY,
				.wdata = NULL, .rdata = &d,
				.wlen = 0, .rlen = 1};
	if (!ec || !data)
		return -EINVAL;
	/*
	 * Query the EC to find out which _Qxx method we need to evaluate.
	 * Note that successful completion of the query causes the ACPI_EC_SCI
	 * bit to be cleared (and thus clearing the interrupt source).
	 */
	result = acpi_ec_transaction_unlocked(ec, &t);
	if (result)
		return result;
	if (!d)
		return -ENODATA;
	*data = d;
	return 0;
}