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
struct gfs2_sbd {int /*<<< orphan*/  sd_fsname; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int gfs2_lm_withdraw (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,char const*,char*,unsigned int) ; 

int gfs2_io_error_bh_i(struct gfs2_sbd *sdp, struct buffer_head *bh,
		       const char *function, char *file, unsigned int line)
{
	int rv;
	rv = gfs2_lm_withdraw(sdp,
		"GFS2: fsid=%s: fatal: I/O error\n"
		"GFS2: fsid=%s:   block = %llu\n"
		"GFS2: fsid=%s:   function = %s, file = %s, line = %u\n",
		sdp->sd_fsname,
		sdp->sd_fsname, (unsigned long long)bh->b_blocknr,
		sdp->sd_fsname, function, file, line);
	return rv;
}