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
struct gfs2_meta_header {int /*<<< orphan*/  mh_type; } ;
struct gfs2_leaf {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
struct gfs2_dirent {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFS2_METATYPE_DI ; 
 scalar_t__ GFS2_METATYPE_LF ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int IS_DINODE ; 
 int IS_LEAF ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_meta_check (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ gfs2_metatype_check (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dirent_first(struct gfs2_inode *dip, struct buffer_head *bh,
			struct gfs2_dirent **dent)
{
	struct gfs2_meta_header *h = (struct gfs2_meta_header *)bh->b_data;

	if (be32_to_cpu(h->mh_type) == GFS2_METATYPE_LF) {
		if (gfs2_meta_check(GFS2_SB(&dip->i_inode), bh))
			return -EIO;
		*dent = (struct gfs2_dirent *)(bh->b_data +
					       sizeof(struct gfs2_leaf));
		return IS_LEAF;
	} else {
		if (gfs2_metatype_check(GFS2_SB(&dip->i_inode), bh, GFS2_METATYPE_DI))
			return -EIO;
		*dent = (struct gfs2_dirent *)(bh->b_data +
					       sizeof(struct gfs2_dinode));
		return IS_DINODE;
	}
}