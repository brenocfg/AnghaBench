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
struct seq_file {struct acpi_video_device* private; } ;
struct acpi_video_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int) ; 
 int acpi_video_device_get_state (struct acpi_video_device*,unsigned long long*) ; 
 int acpi_video_device_query (struct acpi_video_device*,unsigned long long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int acpi_video_device_state_seq_show(struct seq_file *seq, void *offset)
{
	int status;
	struct acpi_video_device *dev = seq->private;
	unsigned long long state;


	if (!dev)
		goto end;

	status = acpi_video_device_get_state(dev, &state);
	seq_printf(seq, "state:     ");
	if (ACPI_SUCCESS(status))
		seq_printf(seq, "0x%02llx\n", state);
	else
		seq_printf(seq, "<not supported>\n");

	status = acpi_video_device_query(dev, &state);
	seq_printf(seq, "query:     ");
	if (ACPI_SUCCESS(status))
		seq_printf(seq, "0x%02llx\n", state);
	else
		seq_printf(seq, "<not supported>\n");

      end:
	return 0;
}