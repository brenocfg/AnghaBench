#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct ide_proc_devset {int (* mulf ) (TYPE_1__*) ;int (* divf ) (TYPE_1__*) ;int min; int max; struct ide_devset* setting; scalar_t__ name; } ;
struct ide_devset {scalar_t__ set; scalar_t__ get; } ;
struct TYPE_5__ {struct ide_proc_devset* settings; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 struct ide_proc_devset* ide_generic_settings ; 
 int ide_read_setting (TYPE_1__*,struct ide_proc_devset const*) ; 
 int /*<<< orphan*/  ide_setting_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_ide_settings_warn () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

__attribute__((used)) static int ide_settings_proc_show(struct seq_file *m, void *v)
{
	const struct ide_proc_devset *setting, *g, *d;
	const struct ide_devset *ds;
	ide_drive_t	*drive = (ide_drive_t *) m->private;
	int		rc, mul_factor, div_factor;

	proc_ide_settings_warn();

	mutex_lock(&ide_setting_mtx);
	g = ide_generic_settings;
	d = drive->settings;
	seq_printf(m, "name\t\t\tvalue\t\tmin\t\tmax\t\tmode\n");
	seq_printf(m, "----\t\t\t-----\t\t---\t\t---\t\t----\n");
	while (g->name || (d && d->name)) {
		/* read settings in the alphabetical order */
		if (g->name && d && d->name) {
			if (strcmp(d->name, g->name) < 0)
				setting = d++;
			else
				setting = g++;
		} else if (d && d->name) {
			setting = d++;
		} else
			setting = g++;
		mul_factor = setting->mulf ? setting->mulf(drive) : 1;
		div_factor = setting->divf ? setting->divf(drive) : 1;
		seq_printf(m, "%-24s", setting->name);
		rc = ide_read_setting(drive, setting);
		if (rc >= 0)
			seq_printf(m, "%-16d", rc * mul_factor / div_factor);
		else
			seq_printf(m, "%-16s", "write-only");
		seq_printf(m, "%-16d%-16d", (setting->min * mul_factor + div_factor - 1) / div_factor, setting->max * mul_factor / div_factor);
		ds = setting->setting;
		if (ds->get)
			seq_printf(m, "r");
		if (ds->set)
			seq_printf(m, "w");
		seq_printf(m, "\n");
	}
	mutex_unlock(&ide_setting_mtx);
	return 0;
}