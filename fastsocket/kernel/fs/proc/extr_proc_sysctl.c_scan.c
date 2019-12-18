#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct file {unsigned long f_pos; } ;
struct ctl_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_4__ {scalar_t__ procname; scalar_t__ ctl_name; } ;
typedef  TYPE_1__ ctl_table ;

/* Variables and functions */
 int proc_sys_fill_cache (struct file*,void*,int /*<<< orphan*/ ,struct ctl_table_header*,TYPE_1__*) ; 

__attribute__((used)) static int scan(struct ctl_table_header *head, ctl_table *table,
		unsigned long *pos, struct file *file,
		void *dirent, filldir_t filldir)
{

	for (; table->ctl_name || table->procname; table++, (*pos)++) {
		int res;

		/* Can't do anything without a proc name */
		if (!table->procname)
			continue;

		if (*pos < file->f_pos)
			continue;

		res = proc_sys_fill_cache(file, dirent, filldir, head, table);
		if (res)
			return res;

		file->f_pos = *pos + 1;
	}
	return 0;
}