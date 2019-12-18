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
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct gfs2_dirent {TYPE_1__ de_inum; int /*<<< orphan*/  de_type; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct inode* ERR_CAST (struct gfs2_dirent*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_dirent_find ; 
 struct gfs2_dirent* gfs2_dirent_search (struct inode*,struct qstr const*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 struct inode* gfs2_inode_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct inode *gfs2_dir_search(struct inode *dir, const struct qstr *name)
{
	struct buffer_head *bh;
	struct gfs2_dirent *dent;
	struct inode *inode;

	dent = gfs2_dirent_search(dir, name, gfs2_dirent_find, &bh);
	if (dent) {
		if (IS_ERR(dent))
			return ERR_CAST(dent);
		inode = gfs2_inode_lookup(dir->i_sb, 
				be16_to_cpu(dent->de_type),
				be64_to_cpu(dent->de_inum.no_addr),
				be64_to_cpu(dent->de_inum.no_formal_ino), 0);
		brelse(bh);
		return inode;
	}
	return ERR_PTR(-ENOENT);
}