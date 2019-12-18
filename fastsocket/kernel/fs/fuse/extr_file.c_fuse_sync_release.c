#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fuse_file {TYPE_1__* reserved_req; int /*<<< orphan*/  fc; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int force; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_RELEASE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_prepare_release (struct fuse_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fuse_request_send (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 

void fuse_sync_release(struct fuse_file *ff, int flags)
{
	WARN_ON(atomic_read(&ff->count) > 1);
	fuse_prepare_release(ff, flags, FUSE_RELEASE);
	ff->reserved_req->force = 1;
	fuse_request_send(ff->fc, ff->reserved_req);
	fuse_put_request(ff->fc, ff->reserved_req);
	kfree(ff);
}