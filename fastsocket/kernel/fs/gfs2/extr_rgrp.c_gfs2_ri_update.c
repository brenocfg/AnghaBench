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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct gfs2_sbd {int sd_rindex_uptodate; } ;
struct gfs2_inode {struct inode i_inode; } ;
struct file_ra_state {int dummy; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  file_ra_state_init (struct file_ra_state*,int /*<<< orphan*/ ) ; 
 int read_rindex_entry (struct gfs2_inode*,struct file_ra_state*) ; 

__attribute__((used)) static int gfs2_ri_update(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct inode *inode = &ip->i_inode;
	struct file_ra_state ra_state;
	int error;

	file_ra_state_init(&ra_state, inode->i_mapping);
	do {
		error = read_rindex_entry(ip, &ra_state);
	} while (error == 0);

	if (error < 0)
		return error;

	sdp->sd_rindex_uptodate = 1;
	return 0;
}