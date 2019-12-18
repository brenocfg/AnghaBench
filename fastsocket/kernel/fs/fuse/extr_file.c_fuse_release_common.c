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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
struct TYPE_4__ {TYPE_1__ release; } ;
struct fuse_req {TYPE_2__ misc; } ;
struct fuse_file {struct fuse_req* reserved_req; } ;
struct file {int /*<<< orphan*/  f_path; int /*<<< orphan*/  f_flags; struct fuse_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_file_put (struct fuse_file*) ; 
 int /*<<< orphan*/  fuse_prepare_release (struct fuse_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void fuse_release_common(struct file *file, int opcode)
{
	struct fuse_file *ff;
	struct fuse_req *req;

	ff = file->private_data;
	if (unlikely(!ff))
		return;

	req = ff->reserved_req;
	fuse_prepare_release(ff, file->f_flags, opcode);

	/* Hold vfsmount and dentry until release is finished */
	path_get(&file->f_path);
	req->misc.release.path = file->f_path;

	/*
	 * Normally this will send the RELEASE request, however if
	 * some asynchronous READ or WRITE requests are outstanding,
	 * the sending will be delayed.
	 */
	fuse_file_put(ff);
}