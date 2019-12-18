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
typedef  int /*<<< orphan*/  u64 ;
struct fuse_open_out {int /*<<< orphan*/  open_flags; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  open_flags; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; } ;
struct fuse_conn {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FOPEN_DIRECT_IO ; 
 int FUSE_OPEN ; 
 int FUSE_OPENDIR ; 
 struct fuse_file* fuse_file_alloc (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_file_free (struct fuse_file*) ; 
 int /*<<< orphan*/  fuse_file_get (struct fuse_file*) ; 
 int fuse_send_open (struct fuse_conn*,int /*<<< orphan*/ ,struct file*,int,struct fuse_open_out*) ; 

int fuse_do_open(struct fuse_conn *fc, u64 nodeid, struct file *file,
		 bool isdir)
{
	struct fuse_open_out outarg;
	struct fuse_file *ff;
	int err;
	int opcode = isdir ? FUSE_OPENDIR : FUSE_OPEN;

	ff = fuse_file_alloc(fc);
	if (!ff)
		return -ENOMEM;

	err = fuse_send_open(fc, nodeid, file, opcode, &outarg);
	if (err) {
		fuse_file_free(ff);
		return err;
	}

	if (isdir)
		outarg.open_flags &= ~FOPEN_DIRECT_IO;

	ff->fh = outarg.fh;
	ff->nodeid = nodeid;
	ff->open_flags = outarg.open_flags;
	file->private_data = fuse_file_get(ff);

	return 0;
}