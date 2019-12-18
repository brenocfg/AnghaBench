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
struct v9fs_session_info {int /*<<< orphan*/  dfltgid; int /*<<< orphan*/  dfltuid; } ;
struct super_block {struct v9fs_session_info* s_fs_info; } ;
struct p9_wstat {int /*<<< orphan*/  length; int /*<<< orphan*/  extension; int /*<<< orphan*/  mode; int /*<<< orphan*/  n_gid; int /*<<< orphan*/  n_uid; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_nlink; int i_blocks; scalar_t__ i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; } ;
typedef  int /*<<< orphan*/  ext ;

/* Variables and functions */
 scalar_t__ MKDEV (int,int) ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  p9mode2unixmode (struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,char*,int*,int*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ v9fs_extended (struct v9fs_session_info*) ; 

void
v9fs_stat2inode(struct p9_wstat *stat, struct inode *inode,
	struct super_block *sb)
{
	char ext[32];
	struct v9fs_session_info *v9ses = sb->s_fs_info;

	inode->i_nlink = 1;

	inode->i_atime.tv_sec = stat->atime;
	inode->i_mtime.tv_sec = stat->mtime;
	inode->i_ctime.tv_sec = stat->mtime;

	inode->i_uid = v9ses->dfltuid;
	inode->i_gid = v9ses->dfltgid;

	if (v9fs_extended(v9ses)) {
		inode->i_uid = stat->n_uid;
		inode->i_gid = stat->n_gid;
	}

	inode->i_mode = p9mode2unixmode(v9ses, stat->mode);
	if ((S_ISBLK(inode->i_mode)) || (S_ISCHR(inode->i_mode))) {
		char type = 0;
		int major = -1;
		int minor = -1;

		strncpy(ext, stat->extension, sizeof(ext));
		sscanf(ext, "%c %u %u", &type, &major, &minor);
		switch (type) {
		case 'c':
			inode->i_mode &= ~S_IFBLK;
			inode->i_mode |= S_IFCHR;
			break;
		case 'b':
			break;
		default:
			P9_DPRINTK(P9_DEBUG_ERROR,
				"Unknown special type %c %s\n", type,
				stat->extension);
		};
		inode->i_rdev = MKDEV(major, minor);
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	} else
		inode->i_rdev = 0;

	i_size_write(inode, stat->length);

	/* not real number of blocks, but 512 byte ones ... */
	inode->i_blocks = (i_size_read(inode) + 512 - 1) >> 9;
}