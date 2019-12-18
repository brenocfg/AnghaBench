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
struct nfs_pgio_header {int /*<<< orphan*/ * verf; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  rpc_list; int /*<<< orphan*/  pages; } ;
struct nfs_write_header {int /*<<< orphan*/  verf; struct nfs_pgio_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfs_write_header* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfs_write_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_wdata_mempool ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct nfs_write_header *nfs_writehdr_alloc(void)
{
	struct nfs_write_header *p = mempool_alloc(nfs_wdata_mempool, GFP_NOFS);

	if (p) {
		struct nfs_pgio_header *hdr = &p->header;

		memset(p, 0, sizeof(*p));
		INIT_LIST_HEAD(&hdr->pages);
		INIT_LIST_HEAD(&hdr->rpc_list);
		spin_lock_init(&hdr->lock);
		atomic_set(&hdr->refcnt, 0);
		hdr->verf = &p->verf;
	}
	return p;
}