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
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; struct inode i_inode; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; int /*<<< orphan*/  el_ea; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_EA2DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_EATYPE_SYS ; 
 int /*<<< orphan*/  GFS2_EA_DATA_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ GFS2_EA_IS_STUFFED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_POSIX_ACL_ACCESS ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_EATTR ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int ea_acl_chmod_unstuffed (struct gfs2_inode*,int /*<<< orphan*/ ,char*) ; 
 int gfs2_ea_find (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_ea_location*) ; 
 int gfs2_setattr_simple (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int gfs2_xattr_acl_chmod(struct gfs2_inode *ip, struct iattr *attr, char *data)
{
	struct inode *inode = &ip->i_inode;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_ea_location el;
	int error;

	error = gfs2_ea_find(ip, GFS2_EATYPE_SYS, GFS2_POSIX_ACL_ACCESS, &el);
	if (error)
		return error;

	if (GFS2_EA_IS_STUFFED(el.el_ea)) {
		error = gfs2_trans_begin(sdp, RES_DINODE + RES_EATTR, 0);
		if (error == 0) {
			gfs2_trans_add_meta(ip->i_gl, el.el_bh);
			memcpy(GFS2_EA2DATA(el.el_ea), data,
			       GFS2_EA_DATA_LEN(el.el_ea));
		}
	} else {
		error = ea_acl_chmod_unstuffed(ip, el.el_ea, data);
	}

	brelse(el.el_bh);
	if (error)
		return error;

	error = gfs2_setattr_simple(inode, attr);
	gfs2_trans_end(sdp);
	return error;
}