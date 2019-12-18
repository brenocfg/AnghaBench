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
struct inode {int dummy; } ;
struct hfs_readdir_data {int /*<<< orphan*/  list; } ;
struct file {struct hfs_readdir_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hfs_readdir_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfs_dir_release(struct inode *inode, struct file *file)
{
	struct hfs_readdir_data *rd = file->private_data;
	if (rd) {
		list_del(&rd->list);
		kfree(rd);
	}
	return 0;
}