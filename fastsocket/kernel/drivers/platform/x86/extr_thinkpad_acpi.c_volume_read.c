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
typedef  int u8 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  onoff (int,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  volume_offset ; 

__attribute__((used)) static int volume_read(struct seq_file *m)
{
	u8 level;

	if (!acpi_ec_read(volume_offset, &level)) {
		seq_printf(m, "level:\t\tunreadable\n");
	} else {
		seq_printf(m, "level:\t\t%d\n", level & 0xf);
		seq_printf(m, "mute:\t\t%s\n", onoff(level, 6));
		seq_printf(m, "commands:\tup, down, mute\n");
		seq_printf(m, "commands:\tlevel <level>"
			       " (<level> is 0-15)\n");
	}

	return 0;
}