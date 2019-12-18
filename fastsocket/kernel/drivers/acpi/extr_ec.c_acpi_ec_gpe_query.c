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
struct acpi_ec {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_sync_query (struct acpi_ec*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_ec_gpe_query(void *ec_cxt)
{
	struct acpi_ec *ec = ec_cxt;
	if (!ec)
		return;
	mutex_lock(&ec->lock);
	acpi_ec_sync_query(ec);
	mutex_unlock(&ec->lock);
}