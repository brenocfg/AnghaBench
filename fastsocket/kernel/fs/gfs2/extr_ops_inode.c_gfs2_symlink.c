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
struct inode {int dummy; } ;
struct TYPE_2__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_dinode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int gfs2_create_inode (struct inode*,struct dentry*,int,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int gfs2_symlink(struct inode *dir, struct dentry *dentry,
			const char *symname)
{
	struct gfs2_sbd *sdp = GFS2_SB(dir);
	int size;

	size = strlen(symname);
	if (size > sdp->sd_sb.sb_bsize - sizeof(struct gfs2_dinode) - 1)
		return -ENAMETOOLONG;

	return gfs2_create_inode(dir, dentry, S_IFLNK | S_IRWXUGO, 0, symname, size, 0);
}