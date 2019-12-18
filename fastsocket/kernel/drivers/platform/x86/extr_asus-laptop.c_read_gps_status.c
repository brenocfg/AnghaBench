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
 int GPS_ON ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  gps_status_handle ; 
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int read_gps_status(void)
{
	unsigned long long status;
	acpi_status rv = AE_OK;

	rv = acpi_evaluate_integer(gps_status_handle, NULL, NULL, &status);
	if (ACPI_FAILURE(rv))
		pr_warning("Error reading GPS status\n");
	else
		return status ? 1 : 0;

	return (hotk->status & GPS_ON) ? 1 : 0;
}