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
struct nfs_commit_data {int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs_commit_data* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfs_commit_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_commit_mempool ; 

struct nfs_commit_data *nfs_commitdata_alloc(void)
{
	struct nfs_commit_data *p = mempool_alloc(nfs_commit_mempool, GFP_NOFS);

	if (p) {
		memset(p, 0, sizeof(*p));
		INIT_LIST_HEAD(&p->pages);
	}
	return p;
}