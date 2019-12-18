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
typedef  char* u32 ;
struct seq_file {struct acpi_video_device* private; } ;
struct TYPE_2__ {scalar_t__ bios; scalar_t__ dvi; scalar_t__ tvout; scalar_t__ lcd; scalar_t__ crt; } ;
struct acpi_video_device {TYPE_1__ flags; scalar_t__ device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int acpi_video_device_info_seq_show(struct seq_file *seq, void *offset)
{
	struct acpi_video_device *dev = seq->private;


	if (!dev)
		goto end;

	seq_printf(seq, "device_id:    0x%04x\n", (u32) dev->device_id);
	seq_printf(seq, "type:         ");
	if (dev->flags.crt)
		seq_printf(seq, "CRT\n");
	else if (dev->flags.lcd)
		seq_printf(seq, "LCD\n");
	else if (dev->flags.tvout)
		seq_printf(seq, "TVOUT\n");
	else if (dev->flags.dvi)
		seq_printf(seq, "DVI\n");
	else
		seq_printf(seq, "UNKNOWN\n");

	seq_printf(seq, "known by bios: %s\n", dev->flags.bios ? "yes" : "no");

      end:
	return 0;
}