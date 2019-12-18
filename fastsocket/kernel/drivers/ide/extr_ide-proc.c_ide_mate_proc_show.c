#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct TYPE_4__ {TYPE_1__* mate; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int ide_mate_proc_show(struct seq_file *m, void *v)
{
	ide_hwif_t	*hwif = (ide_hwif_t *) m->private;

	if (hwif && hwif->mate)
		seq_printf(m, "%s\n", hwif->mate->name);
	else
		seq_printf(m, "(none)\n");
	return 0;
}