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
struct gfs2_sbd {scalar_t__ sd_replayed_blocks; scalar_t__ sd_found_blocks; } ;
struct gfs2_log_header_host {int dummy; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_inode; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buf_lo_before_scan(struct gfs2_jdesc *jd,
			       struct gfs2_log_header_host *head, int pass)
{
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (pass != 0)
		return;

	sdp->sd_found_blocks = 0;
	sdp->sd_replayed_blocks = 0;
}