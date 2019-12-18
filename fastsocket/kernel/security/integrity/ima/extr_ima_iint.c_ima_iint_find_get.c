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
struct ima_iint_cache {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ima_iint_store ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct ima_iint_cache* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct ima_iint_cache *ima_iint_find_get(struct inode *inode)
{
	struct ima_iint_cache *iint;

	rcu_read_lock();
	iint = radix_tree_lookup(&ima_iint_store, (unsigned long)inode);
	if (!iint)
		goto out;
	kref_get(&iint->refcount);
out:
	rcu_read_unlock();
	return iint;
}