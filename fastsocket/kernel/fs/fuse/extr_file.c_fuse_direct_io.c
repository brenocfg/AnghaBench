#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct TYPE_4__ {size_t error; } ;
struct TYPE_5__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_2__ out; } ;
struct fuse_io_priv {int /*<<< orphan*/  async; struct file* file; } ;
struct fuse_file {struct fuse_conn* fc; } ;
struct fuse_conn {size_t max_write; size_t max_read; } ;
struct file {struct fuse_file* private_data; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_6__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 size_t PTR_ERR (struct fuse_req*) ; 
 TYPE_3__* current ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int fuse_get_user_pages (struct fuse_req*,struct iov_iter*,size_t*,int) ; 
 int /*<<< orphan*/  fuse_iter_npages (struct iov_iter*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_release_user_pages (struct fuse_req*,int) ; 
 size_t fuse_send_read (struct fuse_req*,struct fuse_io_priv*,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t fuse_send_write (struct fuse_req*,struct fuse_io_priv*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,struct iovec const*,unsigned long,size_t,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 

ssize_t fuse_direct_io(struct fuse_io_priv *io, const struct iovec *iov,
		       unsigned long nr_segs, size_t count, loff_t *ppos,
		       int write)
{
	struct file *file = io->file;
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;
	size_t nmax = write ? fc->max_write : fc->max_read;
	loff_t pos = *ppos;
	ssize_t res = 0;
	struct fuse_req *req;
	struct iov_iter ii;

	iov_iter_init(&ii, iov, nr_segs, count, 0);

	req = fuse_get_req(fc, fuse_iter_npages(&ii));
	if (IS_ERR(req))
		return PTR_ERR(req);

	while (count) {
		size_t nres;
		fl_owner_t owner = current->files;
		size_t nbytes = min(count, nmax);
		int err = fuse_get_user_pages(req, &ii, &nbytes, write);
		if (err) {
			res = err;
			break;
		}

		if (write)
			nres = fuse_send_write(req, io, pos, nbytes, owner);
		else
			nres = fuse_send_read(req, io, pos, nbytes, owner);

		if (!io->async)
			fuse_release_user_pages(req, !write);
		if (req->out.h.error) {
			if (!res)
				res = req->out.h.error;
			break;
		} else if (nres > nbytes) {
			res = -EIO;
			break;
		}
		count -= nres;
		res += nres;
		pos += nres;
		if (nres != nbytes)
			break;
		if (count) {
			fuse_put_request(fc, req);
			req = fuse_get_req(fc, fuse_iter_npages(&ii));
			if (IS_ERR(req))
				break;
		}
	}
	if (!IS_ERR(req))
		fuse_put_request(fc, req);
	if (res > 0)
		*ppos = pos;

	return res;
}