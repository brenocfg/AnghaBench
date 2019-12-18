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
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  rpc_dentry_operations ; 

__attribute__((used)) static struct dentry *__rpc_lookup_create(struct dentry *parent,
					  struct qstr *name)
{
	struct dentry *dentry;

	dentry = d_lookup(parent, name);
	if (!dentry) {
		dentry = d_alloc(parent, name);
		if (!dentry) {
			dentry = ERR_PTR(-ENOMEM);
			goto out_err;
		}
	}
	if (!dentry->d_inode)
		dentry->d_op = &rpc_dentry_operations;
out_err:
	return dentry;
}