#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int error; } ;
struct TYPE_8__ {TYPE_3__ h; } ;
struct TYPE_5__ {int argpages; } ;
struct fuse_req {int num_pages; TYPE_4__ out; TYPE_2__* page_descs; struct page** pages; TYPE_1__ in; } ;
struct fuse_io_priv {struct file* file; int /*<<< orphan*/  async; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
typedef  int loff_t ;
struct TYPE_6__ {unsigned int offset; unsigned int length; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 size_t fuse_send_write (struct fuse_req*,struct fuse_io_priv*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static int fuse_buffered_write(struct file *file, struct inode *inode,
			       loff_t pos, unsigned count, struct page *page)
{
	int err;
	size_t nres;
	struct fuse_conn *fc = get_fuse_conn(inode);
	unsigned offset = pos & (PAGE_CACHE_SIZE - 1);
	struct fuse_req *req;
	struct fuse_io_priv io = { .async = 0, .file = file };

	if (is_bad_inode(inode))
		return -EIO;

	/*
	 * Make sure writepages on the same page are not mixed up with
	 * plain writes.
	 */
	fuse_wait_on_page_writeback(inode, page->index);

	req = fuse_get_req(fc, 1);
	if (IS_ERR(req))
		return PTR_ERR(req);

	req->in.argpages = 1;
	req->num_pages = 1;
	req->pages[0] = page;
	req->page_descs[0].offset = offset;
	req->page_descs[0].length = count;
	nres = fuse_send_write(req, &io, pos, count, NULL);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (!err && !nres)
		err = -EIO;
	if (!err) {
		pos += nres;
		fuse_write_update_size(inode, pos);
		if (count == PAGE_CACHE_SIZE)
			SetPageUptodate(page);
	}
	fuse_invalidate_attr(inode);
	return err ? err : nres;
}