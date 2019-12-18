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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {scalar_t__ i_no_addr; scalar_t__ i_no_formal_ino; TYPE_2__ i_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_type; TYPE_1__ de_inum; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 scalar_t__ IF2DT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dirent_find ; 
 struct gfs2_dirent* gfs2_dirent_search (struct inode*,struct qstr const*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

int gfs2_dir_check(struct inode *dir, const struct qstr *name,
		   const struct gfs2_inode *ip)
{
	struct buffer_head *bh;
	struct gfs2_dirent *dent;
	int ret = -ENOENT;

	dent = gfs2_dirent_search(dir, name, gfs2_dirent_find, &bh);
	if (dent) {
		if (IS_ERR(dent))
			return PTR_ERR(dent);
		if (ip) {
			if (be64_to_cpu(dent->de_inum.no_addr) != ip->i_no_addr)
				goto out;
			if (be64_to_cpu(dent->de_inum.no_formal_ino) !=
			    ip->i_no_formal_ino)
				goto out;
			if (unlikely(IF2DT(ip->i_inode.i_mode) !=
			    be16_to_cpu(dent->de_type))) {
				gfs2_consist_inode(GFS2_I(dir));
				ret = -EIO;
				goto out;
			}
		}
		ret = 0;
out:
		brelse(bh);
	}
	return ret;
}