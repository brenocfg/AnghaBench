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
struct gfs2_inode {int /*<<< orphan*/  i_eattr; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; int /*<<< orphan*/  el_ea; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int GFS2_EA_DATA_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ GFS2_EA_MAX_NAME_LEN ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int gfs2_ea_find (struct gfs2_inode*,int,char const*,struct gfs2_ea_location*) ; 
 int gfs2_ea_get_copy (struct gfs2_inode*,struct gfs2_ea_location*,void*,size_t) ; 
 scalar_t__ strlen (char const*) ; 

int gfs2_xattr_get(struct inode *inode, int type, const char *name,
		   void *buffer, size_t size)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_ea_location el;
	int error;

	if (!ip->i_eattr)
		return -ENODATA;
	if (strlen(name) > GFS2_EA_MAX_NAME_LEN)
		return -EINVAL;

	error = gfs2_ea_find(ip, type, name, &el);
	if (error)
		return error;
	if (!el.el_ea)
		return -ENODATA;
	if (size)
		error = gfs2_ea_get_copy(ip, &el, buffer, size);
	else
		error = GFS2_EA_DATA_LEN(el.el_ea);
	brelse(el.el_bh);

	return error;
}