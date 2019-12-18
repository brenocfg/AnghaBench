#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_header {scalar_t__ good_bytes; int /*<<< orphan*/  (* release ) (struct nfs_pgio_header*) ;TYPE_1__ pages; int /*<<< orphan*/  error; int /*<<< orphan*/  flags; struct nfs_direct_req* dreq; } ;
struct nfs_page {scalar_t__ wb_bytes; struct page* wb_page; } ;
struct nfs_direct_req {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_direct_complete (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_direct_readpage_release (struct nfs_page*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 scalar_t__ put_dreq (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_direct_read_completion(struct nfs_pgio_header *hdr)
{
	unsigned long bytes = 0;
	struct nfs_direct_req *dreq = hdr->dreq;

	if (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		goto out_put;

	spin_lock(&dreq->lock);
	if (test_bit(NFS_IOHDR_ERROR, &hdr->flags) && (hdr->good_bytes == 0))
		dreq->error = hdr->error;
	else
		dreq->count += hdr->good_bytes;
	spin_unlock(&dreq->lock);

	while (!list_empty(&hdr->pages)) {
		struct nfs_page *req = nfs_list_entry(hdr->pages.next);
		struct page *page = req->wb_page;

		if (!PageCompound(page) && bytes < hdr->good_bytes)
			set_page_dirty(page);
		bytes += req->wb_bytes;
		nfs_list_remove_request(req);
		nfs_direct_readpage_release(req);
	}
out_put:
	if (put_dreq(dreq))
		nfs_direct_complete(dreq);
	hdr->release(hdr);
}