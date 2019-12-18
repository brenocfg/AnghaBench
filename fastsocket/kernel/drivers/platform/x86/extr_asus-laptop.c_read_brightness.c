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
struct backlight_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  brightness_get_handle ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int read_brightness(struct backlight_device *bd)
{
	unsigned long long value;
	acpi_status rv = AE_OK;

	rv = acpi_evaluate_integer(brightness_get_handle, NULL, NULL, &value);
	if (ACPI_FAILURE(rv))
		pr_warning("Error reading brightness\n");

	return value;
}