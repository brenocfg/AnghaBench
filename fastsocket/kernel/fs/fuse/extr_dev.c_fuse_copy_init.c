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
struct iovec {int dummy; } ;
struct fuse_req {int dummy; } ;
struct fuse_copy_state {int write; unsigned long nr_segs; struct iovec const* iov; struct fuse_req* req; struct fuse_conn* fc; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fuse_copy_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_copy_init(struct fuse_copy_state *cs, struct fuse_conn *fc,
			   int write, struct fuse_req *req,
			   const struct iovec *iov, unsigned long nr_segs)
{
	memset(cs, 0, sizeof(*cs));
	cs->fc = fc;
	cs->write = write;
	cs->req = req;
	cs->iov = iov;
	cs->nr_segs = nr_segs;
}