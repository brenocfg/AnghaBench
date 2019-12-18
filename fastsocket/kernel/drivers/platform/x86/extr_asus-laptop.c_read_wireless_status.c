#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long*) ; 
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  wireless_status_handle ; 

__attribute__((used)) static int read_wireless_status(int mask)
{
	unsigned long long status;
	acpi_status rv = AE_OK;

	if (!wireless_status_handle)
		return (hotk->status & mask) ? 1 : 0;

	rv = acpi_evaluate_integer(wireless_status_handle, NULL, NULL, &status);
	if (ACPI_FAILURE(rv))
		pr_warning("Error reading Wireless status\n");
	else
		return (status & mask) ? 1 : 0;

	return (hotk->status & mask) ? 1 : 0;
}