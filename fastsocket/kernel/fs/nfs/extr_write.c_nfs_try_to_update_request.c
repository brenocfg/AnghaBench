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
struct page {int dummy; } ;
struct nfs_page {unsigned int wb_offset; unsigned int wb_bytes; unsigned int wb_pgbase; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 struct nfs_page* ERR_PTR (int) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  nfs_clear_request_commit (struct nfs_page*) ; 
 scalar_t__ nfs_lock_request (struct nfs_page*) ; 
 struct nfs_page* nfs_page_find_request_locked (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int nfs_wait_on_request (struct nfs_page*) ; 
 int nfs_wb_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_page *nfs_try_to_update_request(struct inode *inode,
		struct page *page,
		unsigned int offset,
		unsigned int bytes)
{
	struct nfs_page *req;
	unsigned int rqend;
	unsigned int end;
	int error;

	if (!PagePrivate(page))
		return NULL;

	end = offset + bytes;
	spin_lock(&inode->i_lock);

	for (;;) {
		req = nfs_page_find_request_locked(page);
		if (req == NULL)
			goto out_unlock;

		rqend = req->wb_offset + req->wb_bytes;
		/*
		 * Tell the caller to flush out the request if
		 * the offsets are non-contiguous.
		 * Note: nfs_flush_incompatible() will already
		 * have flushed out requests having wrong owners.
		 */
		if (offset > rqend
		    || end < req->wb_offset)
			goto out_flushme;

		if (nfs_lock_request(req))
			break;

		/* The request is locked, so wait and then retry */
		spin_unlock(&inode->i_lock);
		error = nfs_wait_on_request(req);
		nfs_release_request(req);
		if (error != 0)
			goto out_err;
		spin_lock(&inode->i_lock);
	}

	/* Okay, the request matches. Update the region */
	if (offset < req->wb_offset) {
		req->wb_offset = offset;
		req->wb_pgbase = offset;
	}
	if (end > rqend)
		req->wb_bytes = end - req->wb_offset;
	else
		req->wb_bytes = rqend - req->wb_offset;
out_unlock:
	spin_unlock(&inode->i_lock);
	if (req)
		nfs_clear_request_commit(req);
	return req;
out_flushme:
	spin_unlock(&inode->i_lock);
	nfs_release_request(req);
	error = nfs_wb_page(inode, page);
out_err:
	return ERR_PTR(error);
}