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
struct fuse_conn {int /*<<< orphan*/  (* release ) (struct fuse_conn*) ;int /*<<< orphan*/  inst_mutex; scalar_t__ destroy_req; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_request_free (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fuse_conn*) ; 

void fuse_conn_put(struct fuse_conn *fc)
{
	if (atomic_dec_and_test(&fc->count)) {
		if (fc->destroy_req)
			fuse_request_free(fc->destroy_req);
		mutex_destroy(&fc->inst_mutex);
		fc->release(fc);
	}
}