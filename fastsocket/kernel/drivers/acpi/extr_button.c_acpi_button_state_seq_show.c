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
struct seq_file {struct acpi_device* private; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int acpi_button_state_seq_show(struct seq_file *seq, void *offset)
{
	struct acpi_device *device = seq->private;
	acpi_status status;
	unsigned long long state;

	status = acpi_evaluate_integer(device->handle, "_LID", NULL, &state);
	seq_printf(seq, "state:      %s\n",
		   ACPI_FAILURE(status) ? "unsupported" :
			(state ? "open" : "closed"));
	return 0;
}