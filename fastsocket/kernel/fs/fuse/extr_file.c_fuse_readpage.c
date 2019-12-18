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
typedef  int /*<<< orphan*/  u64 ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int error; } ;
struct TYPE_8__ {int page_zeroing; int argpages; TYPE_3__ h; } ;
struct fuse_req {int num_pages; TYPE_4__ out; TYPE_2__* page_descs; struct page** pages; } ;
struct fuse_io_priv {struct file* file; int /*<<< orphan*/  async; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {size_t length; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 size_t PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_read_update_size (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t fuse_send_read (struct fuse_req*,struct fuse_io_priv*,scalar_t__,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int fuse_readpage(struct file *file, struct page *page)
{
	struct fuse_io_priv io = { .async = 0, .file = file };
	struct inode *inode = page->mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	size_t num_read;
	loff_t pos = page_offset(page);
	size_t count = PAGE_CACHE_SIZE;
	u64 attr_ver;
	int err;

	err = -EIO;
	if (is_bad_inode(inode))
		goto out;

	/*
	 * Page writeback can extend beyond the liftime of the
	 * page-cache page, so make sure we read a properly synced
	 * page.
	 */
	fuse_wait_on_page_writeback(inode, page->index);

	req = fuse_get_req(fc, 1);
	err = PTR_ERR(req);
	if (IS_ERR(req))
		goto out;

	attr_ver = fuse_get_attr_version(fc);

	req->out.page_zeroing = 1;
	req->out.argpages = 1;
	req->num_pages = 1;
	req->pages[0] = page;
	req->page_descs[0].length = count;
	num_read = fuse_send_read(req, &io, pos, count, NULL);
	err = req->out.h.error;
	fuse_put_request(fc, req);

	if (!err) {
		/*
		 * Short read means EOF.  If file size is larger, truncate it
		 */
		if (num_read < count)
			fuse_read_update_size(inode, pos + num_read, attr_ver);

		SetPageUptodate(page);
	}

	fuse_invalidate_attr(inode); /* atime changed */
 out:
	unlock_page(page);
	return err;
}