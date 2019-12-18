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
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_nfs_open_dir_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_closedir(struct inode *inode, struct file *filp)
{
	put_nfs_open_dir_context(filp->private_data);
	return 0;
}