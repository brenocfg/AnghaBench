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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_ON ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_lcd_state () ; 
 scalar_t__ lcd_switch_handle ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  write_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_lcd_state(int value)
{
	int lcd = 0;
	acpi_status status = 0;

	lcd = value ? 1 : 0;

	if (lcd == get_lcd_state())
		return 0;

	if (lcd_switch_handle) {
		status = acpi_evaluate_object(lcd_switch_handle,
					      NULL, NULL, NULL);

		if (ACPI_FAILURE(status))
			pr_warning("Error switching LCD\n");
	}

	write_status(NULL, lcd, LCD_ON);
	return 0;
}