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
struct inode {int dummy; } ;
struct ima_iint_cache {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iint_rcu_free ; 
 int /*<<< orphan*/  ima_enabled ; 
 int /*<<< orphan*/  ima_iint_lock ; 
 int /*<<< orphan*/  ima_iint_store ; 
 struct ima_iint_cache* radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ima_inode_free(struct inode *inode)
{
	struct ima_iint_cache *iint;

	if (!ima_enabled)
		return;

	spin_lock(&ima_iint_lock);
	iint = radix_tree_delete(&ima_iint_store, (unsigned long)inode);
	spin_unlock(&ima_iint_lock);
	if (iint)
		call_rcu(&iint->rcu, iint_rcu_free);
}