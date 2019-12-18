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
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_header {unsigned long good_bytes; int /*<<< orphan*/  (* release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  lseg; int /*<<< orphan*/  verf; int /*<<< orphan*/  flags; int /*<<< orphan*/  error; TYPE_1__ pages; int /*<<< orphan*/  inode; } ;
struct nfs_page {int /*<<< orphan*/  wb_page; int /*<<< orphan*/  wb_verf; int /*<<< orphan*/  wb_context; scalar_t__ wb_bytes; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  NFS_IOHDR_NEED_COMMIT ; 
 int /*<<< orphan*/  NFS_IOHDR_NEED_RESCHED ; 
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_context_set_write_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_inode (struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ ,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_mark_request_dirty (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_set_pageerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_unlock_request (struct nfs_page*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_write_completion(struct nfs_pgio_header *hdr)
{
	struct nfs_commit_info cinfo;
	unsigned long bytes = 0;

	if (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		goto out;
	nfs_init_cinfo_from_inode(&cinfo, hdr->inode);
	while (!list_empty(&hdr->pages)) {
		struct nfs_page *req = nfs_list_entry(hdr->pages.next);

		bytes += req->wb_bytes;
		nfs_list_remove_request(req);
		if (test_bit(NFS_IOHDR_ERROR, &hdr->flags) &&
		    (hdr->good_bytes < bytes)) {
			nfs_set_pageerror(req->wb_page);
			nfs_context_set_write_error(req->wb_context, hdr->error);
			goto remove_req;
		}
		if (test_bit(NFS_IOHDR_NEED_RESCHED, &hdr->flags)) {
			nfs_mark_request_dirty(req);
			goto next;
		}
		if (test_bit(NFS_IOHDR_NEED_COMMIT, &hdr->flags)) {
			memcpy(&req->wb_verf, hdr->verf, sizeof(req->wb_verf));
			nfs_mark_request_commit(req, hdr->lseg, &cinfo);
			goto next;
		}
remove_req:
		nfs_inode_remove_request(req);
next:
		nfs_unlock_request(req);
		nfs_end_page_writeback(req->wb_page);
		nfs_release_request(req);
	}
out:
	hdr->release(hdr);
}