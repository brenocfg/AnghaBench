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
struct qstr {char* name; int len; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {struct dentry* d_parent; int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct dentry* d_alloc (int /*<<< orphan*/ *,struct qstr const*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 

struct dentry * d_alloc_root(struct inode * root_inode)
{
	struct dentry *res = NULL;

	if (root_inode) {
		static const struct qstr name = { .name = "/", .len = 1 };

		res = d_alloc(NULL, &name);
		if (res) {
			res->d_sb = root_inode->i_sb;
			res->d_parent = res;
			d_instantiate(res, root_inode);
		}
	}
	return res;
}