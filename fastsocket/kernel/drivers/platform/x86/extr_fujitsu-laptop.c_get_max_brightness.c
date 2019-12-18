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
typedef  scalar_t__ acpi_status ;
struct TYPE_2__ {unsigned long long max_brightness; int /*<<< orphan*/  acpi_handle; } ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  FUJLAPTOP_DBG_TRACE ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 TYPE_1__* fujitsu ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_max_brightness(void)
{
	unsigned long long state = 0;
	acpi_status status = AE_OK;

	vdbg_printk(FUJLAPTOP_DBG_TRACE, "get max lcd level via RBLL\n");

	status =
	    acpi_evaluate_integer(fujitsu->acpi_handle, "RBLL", NULL, &state);
	if (status < 0)
		return status;

	fujitsu->max_brightness = state;

	return fujitsu->max_brightness;
}