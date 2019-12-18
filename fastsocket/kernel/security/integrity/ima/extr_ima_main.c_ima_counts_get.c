#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mode; } ;
struct ima_iint_cache {int /*<<< orphan*/  refcount; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {int f_mode; TYPE_1__ f_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHECK ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  OPEN_WRITERS ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOMTOU ; 
 int /*<<< orphan*/  iint_free ; 
 int /*<<< orphan*/  ima_enabled ; 
 struct ima_iint_cache* ima_iint_find_get (struct inode*) ; 
 int /*<<< orphan*/  ima_inc_counts (struct ima_iint_cache*,int) ; 
 int /*<<< orphan*/  ima_initialized ; 
 int ima_must_measure (struct ima_iint_cache*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ima_read_write_check (int /*<<< orphan*/ ,struct ima_iint_cache*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ima_counts_get(struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	fmode_t mode = file->f_mode;
	struct ima_iint_cache *iint;
	int rc;

	if (!ima_enabled || !ima_initialized || !S_ISREG(inode->i_mode))
		return;
	iint = ima_iint_find_get(inode);
	if (!iint)
		return;
	mutex_lock(&iint->mutex);
	rc = ima_must_measure(iint, inode, MAY_READ, FILE_CHECK);
	if (rc < 0)
		goto out;

	if (mode & FMODE_WRITE) {
		ima_read_write_check(TOMTOU, iint, inode, dentry->d_name.name);
		goto out;
	}
	ima_read_write_check(OPEN_WRITERS, iint, inode, dentry->d_name.name);
out:
	ima_inc_counts(iint, file->f_mode);
	mutex_unlock(&iint->mutex);

	kref_put(&iint->refcount, iint_free);
}