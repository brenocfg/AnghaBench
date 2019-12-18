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
struct seq_file {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 scalar_t__ ide_gd_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long long) ; 

__attribute__((used)) static int idedisk_capacity_proc_show(struct seq_file *m, void *v)
{
	ide_drive_t*drive = (ide_drive_t *)m->private;

	seq_printf(m, "%llu\n", (long long)ide_gd_capacity(drive));
	return 0;
}