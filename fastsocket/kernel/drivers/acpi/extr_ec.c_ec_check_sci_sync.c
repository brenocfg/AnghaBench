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
typedef  int u8 ;
struct acpi_ec {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ACPI_EC_FLAG_SCI ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_PENDING ; 
 int acpi_ec_sync_query (struct acpi_ec*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_check_sci_sync(struct acpi_ec *ec, u8 state)
{
	if (state & ACPI_EC_FLAG_SCI) {
		if (!test_and_set_bit(EC_FLAGS_QUERY_PENDING, &ec->flags))
			return acpi_ec_sync_query(ec);
	}
	return 0;
}