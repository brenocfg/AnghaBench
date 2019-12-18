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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct ima_iint_cache {int /*<<< orphan*/  refcount; int /*<<< orphan*/  mutex; } ;
struct file {TYPE_1__* f_dentry; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iint_free ; 
 int /*<<< orphan*/  ima_dec_counts (struct ima_iint_cache*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  ima_enabled ; 
 struct ima_iint_cache* ima_iint_find_get (struct inode*) ; 
 int /*<<< orphan*/  ima_initialized ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ima_file_free(struct file *file)
{
	struct inode *inode = file->f_dentry->d_inode;
	struct ima_iint_cache *iint;

	if (!ima_enabled || !ima_initialized || !S_ISREG(inode->i_mode))
		return;
	iint = ima_iint_find_get(inode);
	if (!iint)
		return;

	mutex_lock(&iint->mutex);
	ima_dec_counts(iint, inode, file);
	mutex_unlock(&iint->mutex);
	kref_put(&iint->refcount, iint_free);
}