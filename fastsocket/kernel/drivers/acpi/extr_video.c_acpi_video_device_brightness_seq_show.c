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
struct seq_file {struct acpi_video_device* private; } ;
struct acpi_video_device {TYPE_1__* brightness; } ;
struct TYPE_2__ {int count; int /*<<< orphan*/  curr; int /*<<< orphan*/ * levels; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int
acpi_video_device_brightness_seq_show(struct seq_file *seq, void *offset)
{
	struct acpi_video_device *dev = seq->private;
	int i;


	if (!dev || !dev->brightness) {
		seq_printf(seq, "<not supported>\n");
		return 0;
	}

	seq_printf(seq, "levels: ");
	for (i = 2; i < dev->brightness->count; i++)
		seq_printf(seq, " %d", dev->brightness->levels[i]);
	seq_printf(seq, "\ncurrent: %d\n", dev->brightness->curr);

	return 0;
}