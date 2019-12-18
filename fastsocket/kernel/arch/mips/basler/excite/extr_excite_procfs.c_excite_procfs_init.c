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
struct proc_dir_entry {int size; } ;

/* Variables and functions */
 int EXCITE_SIZE_BOOTROM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct proc_dir_entry* create_proc_read_entry (char*,int /*<<< orphan*/ ,struct proc_dir_entry* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  excite_bootrom_read ; 
 int /*<<< orphan*/  excite_unit_id_proc_fops ; 
 struct proc_dir_entry* proc_create (char*,int /*<<< orphan*/ ,struct proc_dir_entry* const,int /*<<< orphan*/ *) ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ *) ; 

void excite_procfs_init(void)
{
	/* Create & populate /proc/excite */
	struct proc_dir_entry * const pdir = proc_mkdir("excite", NULL);
	if (pdir) {
		struct proc_dir_entry * e;

		e = proc_create("unit_id", S_IRUGO, pdir,
				&excite_unit_id_proc_fops);
		if (e) e->size = 6;

		e = create_proc_read_entry("bootrom", S_IRUGO, pdir,
					   excite_bootrom_read, NULL);
		if (e) e->size = EXCITE_SIZE_BOOTROM;
	}
}