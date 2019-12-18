#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct nfs_readdesc {TYPE_2__* pgio; int /*<<< orphan*/  ctx; } ;
struct nfs_page {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int pg_error; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct nfs_page*) ; 
 struct nfs_page* nfs_create_request (int /*<<< orphan*/ ,struct inode*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (TYPE_2__*,struct nfs_page*) ; 
 int nfs_return_empty_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
readpage_async_filler(void *data, struct page *page)
{
	struct nfs_readdesc *desc = (struct nfs_readdesc *)data;
	struct inode *inode = page->mapping->host;
	struct nfs_page *new;
	unsigned int len;
	int error;

	len = nfs_page_length(page);
	if (len == 0)
		return nfs_return_empty_page(page);

	new = nfs_create_request(desc->ctx, inode, page, 0, len);
	if (IS_ERR(new))
		goto out_error;

	if (len < PAGE_CACHE_SIZE)
		zero_user_segment(page, len, PAGE_CACHE_SIZE);
	if (!nfs_pageio_add_request(desc->pgio, new)) {
		error = desc->pgio->pg_error;
		goto out_unlock;
	}
	return 0;
out_error:
	error = PTR_ERR(new);
out_unlock:
	unlock_page(page);
	return error;
}