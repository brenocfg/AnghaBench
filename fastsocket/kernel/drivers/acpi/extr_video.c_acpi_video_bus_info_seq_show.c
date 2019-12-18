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
struct seq_file {struct acpi_video_bus* private; } ;
struct TYPE_2__ {scalar_t__ post; scalar_t__ rom; scalar_t__ multihead; } ;
struct acpi_video_bus {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int acpi_video_bus_info_seq_show(struct seq_file *seq, void *offset)
{
	struct acpi_video_bus *video = seq->private;


	if (!video)
		goto end;

	seq_printf(seq, "Switching heads:              %s\n",
		   video->flags.multihead ? "yes" : "no");
	seq_printf(seq, "Video ROM:                    %s\n",
		   video->flags.rom ? "yes" : "no");
	seq_printf(seq, "Device to be POSTed on boot:  %s\n",
		   video->flags.post ? "yes" : "no");

      end:
	return 0;
}