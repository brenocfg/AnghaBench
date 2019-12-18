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
typedef  int /*<<< orphan*/  u8 ;
struct transaction {unsigned int wlen; unsigned int rlen; int /*<<< orphan*/ * rdata; int /*<<< orphan*/  const* wdata; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int ENODEV ; 
 int acpi_ec_transaction (int /*<<< orphan*/ ,struct transaction*) ; 
 int /*<<< orphan*/  first_ec ; 

int ec_transaction(u8 command,
		   const u8 * wdata, unsigned wdata_len,
		   u8 * rdata, unsigned rdata_len,
		   int force_poll)
{
	struct transaction t = {.command = command,
				.wdata = wdata, .rdata = rdata,
				.wlen = wdata_len, .rlen = rdata_len};
	if (!first_ec)
		return -ENODEV;

	return acpi_ec_transaction(first_ec, &t);
}