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
struct nlm_file {scalar_t__ f_locks; scalar_t__ f_shares; int /*<<< orphan*/  f_blocks; scalar_t__ f_count; } ;
struct inode {struct file_lock* i_flock; } ;
struct file_lock {int /*<<< orphan*/ * fl_lmops; struct file_lock* fl_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct inode* nlmsvc_file_inode (struct nlm_file*) ; 
 int /*<<< orphan*/  nlmsvc_lock_operations ; 

__attribute__((used)) static inline int
nlm_file_inuse(struct nlm_file *file)
{
	struct inode	 *inode = nlmsvc_file_inode(file);
	struct file_lock *fl;

	if (file->f_count || !list_empty(&file->f_blocks) || file->f_shares)
		return 1;

	for (fl = inode->i_flock; fl; fl = fl->fl_next) {
		if (fl->fl_lmops == &nlmsvc_lock_operations)
			return 1;
	}
	file->f_locks = 0;
	return 0;
}