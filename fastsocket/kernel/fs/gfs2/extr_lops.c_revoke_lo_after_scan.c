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
struct gfs2_sbd {int /*<<< orphan*/  sd_found_revokes; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_jid; int /*<<< orphan*/  jd_inode; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_revoke_clean (struct gfs2_sbd*) ; 

__attribute__((used)) static void revoke_lo_after_scan(struct gfs2_jdesc *jd, int error, int pass)
{
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (error) {
		gfs2_revoke_clean(sdp);
		return;
	}
	if (pass != 1)
		return;

	fs_info(sdp, "jid=%u: Found %u revoke tags\n",
	        jd->jd_jid, sdp->sd_found_revokes);

	gfs2_revoke_clean(sdp);
}