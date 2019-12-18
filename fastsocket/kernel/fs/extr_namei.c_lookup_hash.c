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
struct TYPE_3__ {TYPE_2__* dentry; } ;
struct nameidata {TYPE_1__ path; int /*<<< orphan*/  last; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 struct dentry* __lookup_hash (int /*<<< orphan*/ *,TYPE_2__*,struct nameidata*) ; 
 int inode_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *lookup_hash(struct nameidata *nd)
{
	int err;

	err = inode_permission(nd->path.dentry->d_inode, MAY_EXEC);
	if (err)
		return ERR_PTR(err);
	return __lookup_hash(&nd->last, nd->path.dentry, nd);
}