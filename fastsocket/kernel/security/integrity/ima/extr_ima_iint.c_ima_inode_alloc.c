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
struct ima_iint_cache {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  iint_cache ; 
 int /*<<< orphan*/  ima_enabled ; 
 int /*<<< orphan*/  ima_iint_lock ; 
 int /*<<< orphan*/  ima_iint_store ; 
 struct ima_iint_cache* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ima_iint_cache*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct ima_iint_cache*) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ima_inode_alloc(struct inode *inode)
{
	struct ima_iint_cache *iint = NULL;
	int rc = 0;

	if (!ima_enabled)
		return 0;

	iint = kmem_cache_alloc(iint_cache, GFP_NOFS);
	if (!iint)
		return -ENOMEM;

	rc = radix_tree_preload(GFP_NOFS);
	if (rc < 0)
		goto out;

	spin_lock(&ima_iint_lock);
	rc = radix_tree_insert(&ima_iint_store, (unsigned long)inode, iint);
	spin_unlock(&ima_iint_lock);
	radix_tree_preload_end();
out:
	if (rc < 0)
		kmem_cache_free(iint_cache, iint);

	return rc;
}