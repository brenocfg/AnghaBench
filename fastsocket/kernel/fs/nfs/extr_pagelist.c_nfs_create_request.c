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
struct page {int /*<<< orphan*/  index; } ;
struct nfs_page {unsigned int wb_offset; unsigned int wb_pgbase; unsigned int wb_bytes; int /*<<< orphan*/  wb_kref; int /*<<< orphan*/  wb_context; int /*<<< orphan*/  wb_index; struct page* wb_page; struct nfs_lock_context* wb_lock_context; } ;
struct nfs_open_context {int /*<<< orphan*/  flags; } ;
struct nfs_lock_context {int /*<<< orphan*/  io_count; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_page* ERR_CAST (struct nfs_lock_context*) ; 
 struct nfs_page* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  NFS_CONTEXT_BAD ; 
 int /*<<< orphan*/  get_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nfs_lock_context* nfs_get_lock_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_iocounter_inc (int /*<<< orphan*/ *) ; 
 struct nfs_page* nfs_page_alloc () ; 
 int /*<<< orphan*/  nfs_page_free (struct nfs_page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct nfs_page *
nfs_create_request(struct nfs_open_context *ctx, struct inode *inode,
		   struct page *page,
		   unsigned int offset, unsigned int count)
{
	struct nfs_page		*req;
	struct nfs_lock_context *l_ctx;

	if (test_bit(NFS_CONTEXT_BAD, &ctx->flags))
		return ERR_PTR(-EBADF);
	/* try to allocate the request struct */
	req = nfs_page_alloc();
	if (req == NULL)
		return ERR_PTR(-ENOMEM);

	/* get lock context early so we can deal with alloc failures */
	l_ctx = nfs_get_lock_context(ctx);
	if (IS_ERR(l_ctx)) {
		nfs_page_free(req);
		return ERR_CAST(l_ctx);
	}
	req->wb_lock_context = l_ctx;
	nfs_iocounter_inc(&l_ctx->io_count);

	/* Initialize the request struct. Initially, we assume a
	 * long write-back delay. This will be adjusted in
	 * update_nfs_request below if the region is not locked. */
	req->wb_page    = page;
	req->wb_index	= page->index;
	page_cache_get(page);
	req->wb_offset  = offset;
	req->wb_pgbase	= offset;
	req->wb_bytes   = count;
	req->wb_context = get_nfs_open_context(ctx);
	kref_init(&req->wb_kref);
	return req;
}