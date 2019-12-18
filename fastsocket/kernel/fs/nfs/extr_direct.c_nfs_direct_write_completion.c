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
struct nfs_pgio_header {scalar_t__ error; int /*<<< orphan*/  (* release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  inode; int /*<<< orphan*/  lseg; TYPE_1__ pages; int /*<<< orphan*/  verf; int /*<<< orphan*/  flags; scalar_t__ good_bytes; struct nfs_direct_req* dreq; } ;
struct nfs_page {int /*<<< orphan*/  wb_kref; } ;
struct nfs_direct_req {scalar_t__ flags; scalar_t__ error; int /*<<< orphan*/  lock; int /*<<< orphan*/  verf; int /*<<< orphan*/  count; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int NFS_IOHDR_ERROR ; 
#define  NFS_IOHDR_NEED_COMMIT 129 
#define  NFS_IOHDR_NEED_RESCHED 128 
 int NFS_IOHDR_REDO ; 
 scalar_t__ NFS_ODIRECT_DO_COMMIT ; 
 scalar_t__ NFS_ODIRECT_RESCHED_WRITES ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_direct_write_complete (struct nfs_direct_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_dreq (struct nfs_commit_info*,struct nfs_direct_req*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ ,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 scalar_t__ put_dreq (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_direct_write_completion(struct nfs_pgio_header *hdr)
{
	struct nfs_direct_req *dreq = hdr->dreq;
	struct nfs_commit_info cinfo;
	int bit = -1;
	struct nfs_page *req = nfs_list_entry(hdr->pages.next);

	if (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		goto out_put;

	nfs_init_cinfo_from_dreq(&cinfo, dreq);

	spin_lock(&dreq->lock);

	if (test_bit(NFS_IOHDR_ERROR, &hdr->flags)) {
		dreq->flags = 0;
		dreq->error = hdr->error;
	}
	if (dreq->error != 0)
		bit = NFS_IOHDR_ERROR;
	else {
		dreq->count += hdr->good_bytes;
		if (test_bit(NFS_IOHDR_NEED_RESCHED, &hdr->flags)) {
			dreq->flags = NFS_ODIRECT_RESCHED_WRITES;
			bit = NFS_IOHDR_NEED_RESCHED;
		} else if (test_bit(NFS_IOHDR_NEED_COMMIT, &hdr->flags)) {
			if (dreq->flags == NFS_ODIRECT_RESCHED_WRITES)
				bit = NFS_IOHDR_NEED_RESCHED;
			else if (dreq->flags == 0) {
				memcpy(&dreq->verf, hdr->verf,
				       sizeof(dreq->verf));
				bit = NFS_IOHDR_NEED_COMMIT;
				dreq->flags = NFS_ODIRECT_DO_COMMIT;
			} else if (dreq->flags == NFS_ODIRECT_DO_COMMIT) {
				if (memcmp(&dreq->verf, hdr->verf, sizeof(dreq->verf))) {
					dreq->flags = NFS_ODIRECT_RESCHED_WRITES;
					bit = NFS_IOHDR_NEED_RESCHED;
				} else
					bit = NFS_IOHDR_NEED_COMMIT;
			}
		}
	}
	spin_unlock(&dreq->lock);

	while (!list_empty(&hdr->pages)) {
		req = nfs_list_entry(hdr->pages.next);
		nfs_list_remove_request(req);
		switch (bit) {
		case NFS_IOHDR_NEED_RESCHED:
		case NFS_IOHDR_NEED_COMMIT:
			kref_get(&req->wb_kref);
			nfs_mark_request_commit(req, hdr->lseg, &cinfo);
		}
		nfs_unlock_and_release_request(req);
	}

out_put:
	if (put_dreq(dreq))
		nfs_direct_write_complete(dreq, hdr->inode);
	hdr->release(hdr);
}