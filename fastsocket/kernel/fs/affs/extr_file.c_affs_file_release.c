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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ mmu_private; int /*<<< orphan*/  i_opencnt; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  affs_free_prealloc (struct inode*) ; 
 int /*<<< orphan*/  affs_truncate (struct inode*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
affs_file_release(struct inode *inode, struct file *filp)
{
	pr_debug("AFFS: release(%lu, %d)\n",
		 inode->i_ino, atomic_read(&AFFS_I(inode)->i_opencnt));

	if (atomic_dec_and_test(&AFFS_I(inode)->i_opencnt)) {
		mutex_lock(&inode->i_mutex);
		if (inode->i_size != AFFS_I(inode)->mmu_private)
			affs_truncate(inode);
		affs_free_prealloc(inode);
		mutex_unlock(&inode->i_mutex);
	}

	return 0;
}