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
struct nfs_pageio_descriptor {int dummy; } ;
struct nfs_page {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_pageio_init ) (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_async_read_completion_ops ; 
 struct nfs_page* nfs_create_request (struct nfs_open_context*,struct inode*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int nfs_return_empty_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

int nfs_readpage_async(struct nfs_open_context *ctx, struct inode *inode,
		       struct page *page)
{
	struct nfs_page	*new;
	unsigned int len;
	struct nfs_pageio_descriptor pgio;

	len = nfs_page_length(page);
	if (len == 0)
		return nfs_return_empty_page(page);
	new = nfs_create_request(ctx, inode, page, 0, len);
	if (IS_ERR(new)) {
		unlock_page(page);
		return PTR_ERR(new);
	}
	if (len < PAGE_CACHE_SIZE)
		zero_user_segment(page, len, PAGE_CACHE_SIZE);

	NFS_PROTO(inode)->read_pageio_init(&pgio, inode, &nfs_async_read_completion_ops);
	nfs_pageio_add_request(&pgio, new);
	nfs_pageio_complete(&pgio);
	return 0;
}