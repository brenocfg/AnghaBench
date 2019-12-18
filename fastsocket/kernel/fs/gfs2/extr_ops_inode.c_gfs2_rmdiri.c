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
struct qstr {int dummy; } ;
struct gfs2_inode {int i_entries; } ;

/* Variables and functions */
 int EIO ; 
 int gfs2_change_nlink (struct gfs2_inode*,int) ; 
 scalar_t__ gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dinode_print (struct gfs2_inode*) ; 
 int gfs2_dir_del (struct gfs2_inode*,struct qstr const*) ; 
 struct qstr const gfs2_qdot ; 
 struct qstr const gfs2_qdotdot ; 

__attribute__((used)) static int gfs2_rmdiri(struct gfs2_inode *dip, const struct qstr *name,
		       struct gfs2_inode *ip)
{
	int error;

	if (ip->i_entries != 2) {
		if (gfs2_consist_inode(ip))
			gfs2_dinode_print(ip);
		return -EIO;
	}

	error = gfs2_dir_del(dip, name);
	if (error)
		return error;

	error = gfs2_change_nlink(dip, -1);
	if (error)
		return error;

	error = gfs2_dir_del(ip, &gfs2_qdot);
	if (error)
		return error;

	error = gfs2_dir_del(ip, &gfs2_qdotdot);
	if (error)
		return error;

	/* It looks odd, but it really should be done twice */
	error = gfs2_change_nlink(ip, -1);
	if (error)
		return error;

	error = gfs2_change_nlink(ip, -1);
	if (error)
		return error;

	return error;
}