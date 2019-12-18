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
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/ * d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* __rpc_lookup_create (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static struct dentry *__rpc_lookup_create_exclusive(struct dentry *parent,
					  struct qstr *name)
{
	struct dentry *dentry;

	dentry = __rpc_lookup_create(parent, name);
	if (IS_ERR(dentry))
		return dentry;
	if (dentry->d_inode == NULL)
		return dentry;
	dput(dentry);
	return ERR_PTR(-EEXIST);
}