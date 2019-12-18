#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  nodeid; } ;
struct fuse_dirent {scalar_t__ namelen; int /*<<< orphan*/  off; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  name; } ;
struct fuse_direntplus {TYPE_1__ entry_out; struct fuse_dirent dirent; } ;
struct file {int /*<<< orphan*/  f_pos; } ;
typedef  int (* filldir_t ) (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int EIO ; 
 size_t FUSE_DIRENTPLUS_SIZE (struct fuse_direntplus*) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 size_t FUSE_NAME_OFFSET_DIRENTPLUS ; 
 int fuse_direntplus_link (struct file*,struct fuse_direntplus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_force_forget (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_dirplusfile(char *buf, size_t nbytes, struct file *file,
			     void *dstbuf, filldir_t filldir, u64 attr_version)
{
	struct fuse_direntplus *direntplus;
	struct fuse_dirent *dirent;
	size_t reclen;
	int over = 0;
	int ret;

	while (nbytes >= FUSE_NAME_OFFSET_DIRENTPLUS) {
		direntplus = (struct fuse_direntplus *) buf;
		dirent = &direntplus->dirent;
		reclen = FUSE_DIRENTPLUS_SIZE(direntplus);

		if (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			return -EIO;
		if (reclen > nbytes)
			break;

		if (!over) {
			/* We fill entries into dstbuf only as much as
			   it can hold. But we still continue iterating
			   over remaining entries to link them. If not,
			   we need to send a FORGET for each of those
			   which we did not link.
			*/
			over = filldir(dstbuf, dirent->name, dirent->namelen,
				       file->f_pos, dirent->ino,
				       dirent->type);
			file->f_pos = dirent->off;
		}

		buf += reclen;
		nbytes -= reclen;

		ret = fuse_direntplus_link(file, direntplus, attr_version);
		if (ret)
			fuse_force_forget(file, direntplus->entry_out.nodeid);
	}

	return 0;
}