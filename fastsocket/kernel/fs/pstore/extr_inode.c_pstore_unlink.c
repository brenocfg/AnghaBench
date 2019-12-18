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
struct pstore_private {TYPE_2__* psi; int /*<<< orphan*/  count; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct inode {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* erase ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  i_ctime; struct pstore_private* i_private; } ;

/* Variables and functions */
 int simple_unlink (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int pstore_unlink(struct inode *dir, struct dentry *dentry)
{
	struct pstore_private *p = dentry->d_inode->i_private;

	if (p->psi->erase)
		p->psi->erase(p->type, p->id, p->count,
			      dentry->d_inode->i_ctime, p->psi);

	return simple_unlink(dir, dentry);
}