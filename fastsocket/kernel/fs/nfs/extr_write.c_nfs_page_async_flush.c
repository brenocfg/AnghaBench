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
struct nfs_pageio_descriptor {int pg_error; } ;
struct nfs_page {int /*<<< orphan*/  wb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  PG_CLEAN ; 
 int PTR_ERR (struct nfs_page*) ; 
 struct nfs_page* nfs_find_and_lock_request (struct page*,int) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_redirty_request (struct nfs_page*) ; 
 int nfs_set_page_writeback (struct page*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_page_async_flush(struct nfs_pageio_descriptor *pgio,
				struct page *page, bool nonblock)
{
	struct nfs_page *req;
	int ret = 0;

	req = nfs_find_and_lock_request(page, nonblock);
	if (!req)
		goto out;
	ret = PTR_ERR(req);
	if (IS_ERR(req))
		goto out;

	ret = nfs_set_page_writeback(page);
	BUG_ON(ret != 0);
	BUG_ON(test_bit(PG_CLEAN, &req->wb_flags));

	if (!nfs_pageio_add_request(pgio, req)) {
		nfs_redirty_request(req);
		ret = pgio->pg_error;
	}
out:
	return ret;
}