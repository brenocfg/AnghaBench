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
struct seq_file {struct acpi_thermal* private; } ;
struct acpi_thermal {int /*<<< orphan*/  temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  KELVIN_TO_CELSIUS (int /*<<< orphan*/ ) ; 
 int acpi_thermal_get_temperature (struct acpi_thermal*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_thermal_temp_seq_show(struct seq_file *seq, void *offset)
{
	int result = 0;
	struct acpi_thermal *tz = seq->private;


	if (!tz)
		goto end;

	result = acpi_thermal_get_temperature(tz);
	if (result)
		goto end;

	seq_printf(seq, "temperature:             %ld C\n",
		   KELVIN_TO_CELSIUS(tz->temperature));

      end:
	return 0;
}