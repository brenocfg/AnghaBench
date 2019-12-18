#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_4__* mapping; } ;
struct nfs_page {struct nfs_open_context* wb_context; struct page* wb_page; struct nfs_lock_context* wb_lock_context; } ;
struct nfs_open_context {TYPE_2__* dentry; } ;
struct TYPE_8__ {scalar_t__ l_owner; scalar_t__ l_pid; } ;
struct nfs_lock_context {TYPE_3__ lockowner; } ;
struct file {int dummy; } ;
struct TYPE_10__ {scalar_t__ files; scalar_t__ tgid; } ;
struct TYPE_9__ {int /*<<< orphan*/  host; } ;
struct TYPE_7__ {TYPE_1__* d_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/ * i_flock; } ;

/* Variables and functions */
 TYPE_5__* current ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 struct nfs_page* nfs_page_find_request (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int nfs_wb_page (int /*<<< orphan*/ ,struct page*) ; 

int nfs_flush_incompatible(struct file *file, struct page *page)
{
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	struct nfs_lock_context *l_ctx;
	struct nfs_page	*req;
	int do_flush, status;
	/*
	 * Look for a request corresponding to this page. If there
	 * is one, and it belongs to another file, we flush it out
	 * before we try to copy anything into the page. Do this
	 * due to the lack of an ACCESS-type call in NFSv2.
	 * Also do the same if we find a request from an existing
	 * dropped page.
	 */
	do {
		req = nfs_page_find_request(page);
		if (req == NULL)
			return 0;
		l_ctx = req->wb_lock_context;
		do_flush = req->wb_page != page || req->wb_context != ctx;
		if (l_ctx && ctx->dentry->d_inode->i_flock != NULL) {
			do_flush |= l_ctx->lockowner.l_owner != current->files
				|| l_ctx->lockowner.l_pid != current->tgid;
		}
		nfs_release_request(req);
		if (!do_flush)
			return 0;
		status = nfs_wb_page(page->mapping->host, page);
	} while (status == 0);
	return status;
}