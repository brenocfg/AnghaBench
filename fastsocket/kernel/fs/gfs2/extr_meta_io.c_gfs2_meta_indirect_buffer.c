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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; int /*<<< orphan*/  i_inode; } ;
struct gfs2_glock {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_WAIT ; 
 int EIO ; 
 int /*<<< orphan*/  GFS2_METATYPE_DI ; 
 int /*<<< orphan*/  GFS2_METATYPE_IN ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int gfs2_meta_read (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 

int gfs2_meta_indirect_buffer(struct gfs2_inode *ip, int height, u64 num,
			      struct buffer_head **bhp)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_glock *gl = ip->i_gl;
	struct buffer_head *bh;
	int ret = 0;
	u32 mtype = height ? GFS2_METATYPE_IN : GFS2_METATYPE_DI;

	ret = gfs2_meta_read(gl, num, DIO_WAIT, &bh);
	if (ret == 0 && gfs2_metatype_check(sdp, bh, mtype)) {
		brelse(bh);
		ret = -EIO;
	}
	*bhp = bh;
	return ret;
}