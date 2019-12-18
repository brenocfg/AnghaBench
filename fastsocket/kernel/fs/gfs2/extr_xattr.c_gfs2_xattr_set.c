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
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_eattr; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; scalar_t__ el_ea; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 int EPERM ; 
 int ERANGE ; 
 int GFS2_DIF_APPENDONLY ; 
 int /*<<< orphan*/  GFS2_EA_IS_STUFFED (scalar_t__) ; 
 unsigned int GFS2_EA_MAX_NAME_LEN ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 scalar_t__ ea_check_size (struct gfs2_sbd*,unsigned int,size_t) ; 
 int ea_init (struct gfs2_inode*,int,char const*,void const*,size_t) ; 
 int ea_set_i (struct gfs2_inode*,int,char const*,void const*,size_t,struct gfs2_ea_location*) ; 
 int /*<<< orphan*/  ea_set_remove_unstuffed (struct gfs2_inode*,struct gfs2_ea_location*) ; 
 int gfs2_ea_find (struct gfs2_inode*,int,char const*,struct gfs2_ea_location*) ; 
 int gfs2_xattr_remove (struct inode*,int,char const*) ; 
 unsigned int strlen (char const*) ; 

int gfs2_xattr_set(struct inode *inode, int type, const char *name,
		   const void *value, size_t size, int flags)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_ea_location el;
	unsigned int namel = strlen(name);
	int error;

	if (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		return -EPERM;
	if (namel > GFS2_EA_MAX_NAME_LEN)
		return -ERANGE;

	if (value == NULL)
		return gfs2_xattr_remove(inode, type, name);

	if (ea_check_size(sdp, namel, size))
		return -ERANGE;

	if (!ip->i_eattr) {
		if (flags & XATTR_REPLACE)
			return -ENODATA;
		return ea_init(ip, type, name, value, size);
	}

	error = gfs2_ea_find(ip, type, name, &el);
	if (error)
		return error;

	if (el.el_ea) {
		if (ip->i_diskflags & GFS2_DIF_APPENDONLY) {
			brelse(el.el_bh);
			return -EPERM;
		}

		error = -EEXIST;
		if (!(flags & XATTR_CREATE)) {
			int unstuffed = !GFS2_EA_IS_STUFFED(el.el_ea);
			error = ea_set_i(ip, type, name, value, size, &el);
			if (!error && unstuffed)
				ea_set_remove_unstuffed(ip, &el);
		}

		brelse(el.el_bh);
		return error;
	}

	error = -ENODATA;
	if (!(flags & XATTR_REPLACE))
		error = ea_set_i(ip, type, name, value, size, NULL);

	return error;
}