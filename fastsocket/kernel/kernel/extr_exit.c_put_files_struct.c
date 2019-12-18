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
struct fdtable {int dummy; } ;
struct files_struct {struct fdtable fdtab; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_files (struct files_struct*) ; 
 int /*<<< orphan*/  files_cachep ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  free_fdtable (struct fdtable*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct files_struct*) ; 

void put_files_struct(struct files_struct *files)
{
	struct fdtable *fdt;

	if (atomic_dec_and_test(&files->count)) {
		close_files(files);
		/*
		 * Free the fd and fdset arrays if we expanded them.
		 * If the fdtable was embedded, pass files for freeing
		 * at the end of the RCU grace period. Otherwise,
		 * you can free files immediately.
		 */
		fdt = files_fdtable(files);
		if (fdt != &files->fdtab)
			kmem_cache_free(files_cachep, files);
		free_fdtable(fdt);
	}
}