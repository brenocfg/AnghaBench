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
struct nfs_pgio_header {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  rpc_list; int /*<<< orphan*/  pages; } ;
struct nfs_read_header {struct nfs_pgio_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfs_read_header* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_rdata_cachep ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct nfs_read_header *nfs_readhdr_alloc(void)
{
	struct nfs_read_header *rhdr;

	rhdr = kmem_cache_zalloc(nfs_rdata_cachep, GFP_KERNEL);
	if (rhdr) {
		struct nfs_pgio_header *hdr = &rhdr->header;

		INIT_LIST_HEAD(&hdr->pages);
		INIT_LIST_HEAD(&hdr->rpc_list);
		spin_lock_init(&hdr->lock);
		atomic_set(&hdr->refcnt, 0);
	}
	return rhdr;
}