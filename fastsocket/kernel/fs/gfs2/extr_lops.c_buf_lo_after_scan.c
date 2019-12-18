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
struct gfs2_sbd {int /*<<< orphan*/  sd_found_blocks; int /*<<< orphan*/  sd_replayed_blocks; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_jid; int /*<<< orphan*/  jd_inode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_meta_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buf_lo_after_scan(struct gfs2_jdesc *jd, int error, int pass)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (error) {
		gfs2_meta_sync(ip->i_gl);
		return;
	}
	if (pass != 1)
		return;

	gfs2_meta_sync(ip->i_gl);

	fs_info(sdp, "jid=%u: Replayed %u of %u blocks\n",
	        jd->jd_jid, sdp->sd_replayed_blocks, sdp->sd_found_blocks);
}