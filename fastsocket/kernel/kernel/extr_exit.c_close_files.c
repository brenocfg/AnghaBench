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
struct files_struct {int dummy; } ;
struct file {int dummy; } ;
struct fdtable {int max_fds; int /*<<< orphan*/ * fd; TYPE_1__* open_fds; } ;
struct TYPE_2__ {unsigned long* fds_bits; } ;

/* Variables and functions */
 int __NFDBITS ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  filp_close (struct file*,struct files_struct*) ; 
 struct file* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_files(struct files_struct * files)
{
	int i, j;
	struct fdtable *fdt;

	j = 0;

	/*
	 * It is safe to dereference the fd table without RCU or
	 * ->file_lock because this is the last reference to the
	 * files structure.
	 */
	fdt = files_fdtable(files);
	for (;;) {
		unsigned long set;
		i = j * __NFDBITS;
		if (i >= fdt->max_fds)
			break;
		set = fdt->open_fds->fds_bits[j++];
		while (set) {
			if (set & 1) {
				struct file * file = xchg(&fdt->fd[i], NULL);
				if (file) {
					filp_close(file, files);
					cond_resched();
				}
			}
			i++;
			set >>= 1;
		}
	}
}