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
struct TYPE_2__ {unsigned long long brightness_level; int brightness_changed; int /*<<< orphan*/  acpi_handle; } ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  FUJLAPTOP_DBG_TRACE ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 TYPE_1__* fujitsu ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_lcd_level(void)
{
	unsigned long long state = 0;
	acpi_status status = AE_OK;

	vdbg_printk(FUJLAPTOP_DBG_TRACE, "get lcd level via GBLL\n");

	status =
	    acpi_evaluate_integer(fujitsu->acpi_handle, "GBLL", NULL, &state);
	if (status < 0)
		return status;

	fujitsu->brightness_level = state & 0x0fffffff;

	if (state & 0x80000000)
		fujitsu->brightness_changed = 1;
	else
		fujitsu->brightness_changed = 0;

	return fujitsu->brightness_level;
}