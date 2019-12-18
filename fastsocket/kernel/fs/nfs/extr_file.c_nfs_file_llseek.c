#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_12__ {TYPE_4__* dentry; } ;
struct file {TYPE_2__* f_mapping; TYPE_6__ f_path; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {TYPE_3__ d_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_1__ d_name; TYPE_5__* d_parent; } ;
struct TYPE_8__ {struct inode* host; } ;

/* Variables and functions */
 int SEEK_END ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generic_file_llseek_unlocked (struct file*,int /*<<< orphan*/ ,int) ; 
 int nfs_revalidate_file_size (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t nfs_file_llseek(struct file *filp, loff_t offset, int origin)
{
	loff_t loff;

	dprintk("NFS: llseek file(%s/%s, %lld, %d)\n",
			filp->f_path.dentry->d_parent->d_name.name,
			filp->f_path.dentry->d_name.name,
			offset, origin);

	/* origin == SEEK_END => we must revalidate the cached file length */
	if (origin == SEEK_END) {
		struct inode *inode = filp->f_mapping->host;

		int retval = nfs_revalidate_file_size(inode, filp);
		if (retval < 0)
			return (loff_t)retval;

		spin_lock(&inode->i_lock);
		loff = generic_file_llseek_unlocked(filp, offset, origin);
		spin_unlock(&inode->i_lock);
	} else
		loff = generic_file_llseek_unlocked(filp, offset, origin);
	return loff;
}