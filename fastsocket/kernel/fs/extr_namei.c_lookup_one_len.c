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
struct qstr {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct dentry* __lookup_hash (struct qstr*,struct dentry*,int /*<<< orphan*/ *) ; 
 int __lookup_one_len (char const*,struct qstr*,struct dentry*,int) ; 
 int inode_permission (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

struct dentry *lookup_one_len(const char *name, struct dentry *base, int len)
{
	int err;
	struct qstr this;

	WARN_ON_ONCE(!mutex_is_locked(&base->d_inode->i_mutex));

	err = __lookup_one_len(name, &this, base, len);
	if (err)
		return ERR_PTR(err);

	err = inode_permission(base->d_inode, MAY_EXEC);
	if (err)
		return ERR_PTR(err);
	return __lookup_hash(&this, base, NULL);
}