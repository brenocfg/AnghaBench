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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct inode {int /*<<< orphan*/ * d_op; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inum_host {int /*<<< orphan*/  no_addr; int /*<<< orphan*/  no_formal_ino; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_no_formal_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  GFS2_BLKST_DINODE ; 
 TYPE_1__* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  gfs2_dops ; 
 struct inode* gfs2_ilookup (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* gfs2_lookup_by_inum (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *gfs2_get_dentry(struct super_block *sb,
				      struct gfs2_inum_host *inum)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct inode *inode;
	struct dentry *dentry;

	inode = gfs2_ilookup(sb, inum->no_addr, 0);
	if (inode) {
		if (GFS2_I(inode)->i_no_formal_ino != inum->no_formal_ino) {
			iput(inode);
			return ERR_PTR(-ESTALE);
		}
	} else {
		inode = gfs2_lookup_by_inum(sdp, inum->no_addr,
					    &inum->no_formal_ino,
					    GFS2_BLKST_DINODE);
		if (inode == ERR_PTR(-ENOENT))
			inode = gfs2_ilookup(sb, inum->no_addr, 0);
	}

	if (IS_ERR(inode))
		return ERR_CAST(inode);

	dentry = d_obtain_alias(inode);
	if (!IS_ERR(dentry))
		dentry->d_op = &gfs2_dops;
	return dentry;
}