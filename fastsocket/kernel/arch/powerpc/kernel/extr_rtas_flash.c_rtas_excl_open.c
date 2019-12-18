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
struct proc_dir_entry {int /*<<< orphan*/  count; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flash_file_open_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtas_excl_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *dp = PDE(inode);

	/* Enforce exclusive open with use count of PDE */
	spin_lock(&flash_file_open_lock);
	if (atomic_read(&dp->count) > 2) {
		spin_unlock(&flash_file_open_lock);
		return -EBUSY;
	}

	atomic_inc(&dp->count);
	spin_unlock(&flash_file_open_lock);
	
	return 0;
}