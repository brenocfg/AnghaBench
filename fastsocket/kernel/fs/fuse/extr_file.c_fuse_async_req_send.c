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
struct fuse_req {int /*<<< orphan*/  end; struct fuse_io_priv* io; } ;
struct fuse_io_priv {size_t size; int /*<<< orphan*/  lock; int /*<<< orphan*/  reqs; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fuse_get_request (struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_aio_complete_req ; 
 int /*<<< orphan*/  fuse_request_send_background (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t fuse_async_req_send(struct fuse_conn *fc, struct fuse_req *req,
		size_t num_bytes, struct fuse_io_priv *io)
{
	spin_lock(&io->lock);
	io->size += num_bytes;
	io->reqs++;
	spin_unlock(&io->lock);

	req->io = io;
	req->end = fuse_aio_complete_req;

	__fuse_get_request(req);
	fuse_request_send_background(fc, req);

	return num_bytes;
}