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
struct gfs2_inode {scalar_t__ i_no_addr; scalar_t__ i_no_formal_ino; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int gfs2_lm_withdraw (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int /*<<< orphan*/ ,char const*,char*,unsigned int) ; 

int gfs2_consist_inode_i(struct gfs2_inode *ip, int cluster_wide,
			 const char *function, char *file, unsigned int line)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	int rv;
	rv = gfs2_lm_withdraw(sdp,
		"GFS2: fsid=%s: fatal: filesystem consistency error\n"
		"GFS2: fsid=%s:   inode = %llu %llu\n"
		"GFS2: fsid=%s:   function = %s, file = %s, line = %u\n",
		sdp->sd_fsname,
		sdp->sd_fsname, (unsigned long long)ip->i_no_formal_ino,
		(unsigned long long)ip->i_no_addr,
		sdp->sd_fsname, function, file, line);
	return rv;
}