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
struct fuse_req {scalar_t__ stolen_file; scalar_t__ waiting; int /*<<< orphan*/  count; } ;
struct fuse_conn {int /*<<< orphan*/  num_waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_request_free (struct fuse_req*) ; 
 int /*<<< orphan*/  put_reserved_req (struct fuse_conn*,struct fuse_req*) ; 

void fuse_put_request(struct fuse_conn *fc, struct fuse_req *req)
{
	if (atomic_dec_and_test(&req->count)) {
		if (req->waiting)
			atomic_dec(&fc->num_waiting);

		if (req->stolen_file)
			put_reserved_req(fc, req);
		else
			fuse_request_free(req);
	}
}