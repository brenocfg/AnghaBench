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
struct udf_fileident_bh {scalar_t__ sbh; scalar_t__ ebh; } ;
struct qstr {char* name; int len; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  extLocation; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  udf_find_entry (TYPE_2__*,struct qstr*,struct udf_fileident_bh*,struct fileIdentDesc*) ; 
 struct inode* udf_iget (int /*<<< orphan*/ ,struct kernel_lb_addr*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *udf_get_parent(struct dentry *child)
{
	struct kernel_lb_addr tloc;
	struct inode *inode = NULL;
	struct qstr dotdot = {.name = "..", .len = 2};
	struct fileIdentDesc cfi;
	struct udf_fileident_bh fibh;

	lock_kernel();
	if (!udf_find_entry(child->d_inode, &dotdot, &fibh, &cfi))
		goto out_unlock;

	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);

	tloc = lelb_to_cpu(cfi.icb.extLocation);
	inode = udf_iget(child->d_inode->i_sb, &tloc);
	if (!inode)
		goto out_unlock;
	unlock_kernel();

	return d_obtain_alias(inode);
out_unlock:
	unlock_kernel();
	return ERR_PTR(-EACCES);
}