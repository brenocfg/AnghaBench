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
struct fuse_dirent {scalar_t__ namelen; int /*<<< orphan*/  off; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  name; } ;
struct file {int /*<<< orphan*/  f_pos; } ;
typedef  int (* filldir_t ) (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int EIO ; 
 size_t FUSE_DIRENT_SIZE (struct fuse_dirent*) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 size_t FUSE_NAME_OFFSET ; 

__attribute__((used)) static int parse_dirfile(char *buf, size_t nbytes, struct file *file,
			 void *dstbuf, filldir_t filldir)
{
	while (nbytes >= FUSE_NAME_OFFSET) {
		struct fuse_dirent *dirent = (struct fuse_dirent *) buf;
		size_t reclen = FUSE_DIRENT_SIZE(dirent);
		int over;
		if (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			return -EIO;
		if (reclen > nbytes)
			break;

		over = filldir(dstbuf, dirent->name, dirent->namelen,
			       file->f_pos, dirent->ino, dirent->type);
		if (over)
			break;

		buf += reclen;
		nbytes -= reclen;
		file->f_pos = dirent->off;
	}

	return 0;
}