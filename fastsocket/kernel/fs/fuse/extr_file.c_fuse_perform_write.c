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
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int error; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_2__ out; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 size_t fuse_fill_write_pages (struct fuse_req*,struct address_space*,struct iov_iter*,size_t) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,unsigned int) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 size_t fuse_send_write_pages (struct fuse_req*,struct file*,struct inode*,size_t,size_t) ; 
 unsigned int fuse_wr_pages (size_t,scalar_t__) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,size_t) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static ssize_t fuse_perform_write(struct file *file,
				  struct address_space *mapping,
				  struct iov_iter *ii, loff_t pos)
{
	struct inode *inode = mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err = 0;
	ssize_t res = 0;

	if (is_bad_inode(inode))
		return -EIO;

	do {
		struct fuse_req *req;
		ssize_t count;
		unsigned nr_pages = fuse_wr_pages(pos, iov_iter_count(ii));

		req = fuse_get_req(fc, nr_pages);
		if (IS_ERR(req)) {
			err = PTR_ERR(req);
			break;
		}

		count = fuse_fill_write_pages(req, mapping, ii, pos);
		if (count <= 0) {
			err = count;
		} else {
			size_t num_written;

			num_written = fuse_send_write_pages(req, file, inode,
							    pos, count);
			err = req->out.h.error;
			if (!err) {
				res += num_written;
				pos += num_written;

				/* break out of the loop on short write */
				if (num_written != count)
					err = -EIO;
			}
		}
		fuse_put_request(fc, req);
	} while (!err && iov_iter_count(ii));

	if (res > 0)
		fuse_write_update_size(inode, pos);

	fuse_invalidate_attr(inode);

	return res > 0 ? res : err;
}