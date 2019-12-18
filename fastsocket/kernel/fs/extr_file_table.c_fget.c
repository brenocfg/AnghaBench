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
struct file {int /*<<< orphan*/  f_count; } ;
struct TYPE_2__ {struct files_struct* files; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 struct file* fcheck_files (struct files_struct*,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct file *fget(unsigned int fd)
{
	struct file *file;
	struct files_struct *files = current->files;

	rcu_read_lock();
	file = fcheck_files(files, fd);
	if (file) {
		if (!atomic_long_inc_not_zero(&file->f_count)) {
			/* File object ref couldn't be taken */
			rcu_read_unlock();
			return NULL;
		}
	}
	rcu_read_unlock();

	return file;
}