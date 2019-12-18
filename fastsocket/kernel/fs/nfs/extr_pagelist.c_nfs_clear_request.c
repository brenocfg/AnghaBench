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
struct nfs_page {struct nfs_open_context* wb_context; struct nfs_lock_context* wb_lock_context; struct page* wb_page; } ;
struct nfs_open_context {int dummy; } ;
struct nfs_lock_context {int /*<<< orphan*/  io_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_iocounter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 

__attribute__((used)) static void nfs_clear_request(struct nfs_page *req)
{
	struct page *page = req->wb_page;
	struct nfs_open_context *ctx = req->wb_context;
	struct nfs_lock_context *l_ctx = req->wb_lock_context;

	if (page != NULL) {
		page_cache_release(page);
		req->wb_page = NULL;
	}
	if (l_ctx != NULL) {
		nfs_iocounter_dec(&l_ctx->io_count);
		nfs_put_lock_context(l_ctx);
		req->wb_lock_context = NULL;
	}
	if (ctx != NULL) {
		put_nfs_open_context(ctx);
		req->wb_context = NULL;
	}
}