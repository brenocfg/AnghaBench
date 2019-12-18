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
struct acpi_ec {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int ACPI_EC_DELAY ; 
 int ETIME ; 
 int /*<<< orphan*/  ec_check_ibf0 (struct acpi_ec*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ec_wait_ibf0(struct acpi_ec *ec)
{
	unsigned long delay = jiffies + msecs_to_jiffies(ACPI_EC_DELAY);
	/* interrupt wait manually if GPE mode is not active */
	while (time_before(jiffies, delay))
		if (wait_event_timeout(ec->wait, ec_check_ibf0(ec),
					msecs_to_jiffies(1)))
			return 0;
	return -ETIME;
}