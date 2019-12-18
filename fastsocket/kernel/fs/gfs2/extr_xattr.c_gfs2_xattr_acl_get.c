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
struct gfs2_inode {int dummy; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_bh; int /*<<< orphan*/  el_ea; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFS2_EATYPE_SYS ; 
 int GFS2_EA_DATA_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int gfs2_ea_find (struct gfs2_inode*,int /*<<< orphan*/ ,char const*,struct gfs2_ea_location*) ; 
 int gfs2_ea_get_copy (struct gfs2_inode*,struct gfs2_ea_location*,char*,int) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

int gfs2_xattr_acl_get(struct gfs2_inode *ip, const char *name, char **ppdata)
{
	struct gfs2_ea_location el;
	int error;
	int len;
	char *data;

	error = gfs2_ea_find(ip, GFS2_EATYPE_SYS, name, &el);
	if (error)
		return error;
	if (!el.el_ea)
		goto out;
	if (!GFS2_EA_DATA_LEN(el.el_ea))
		goto out;

	len = GFS2_EA_DATA_LEN(el.el_ea);
	data = kmalloc(len, GFP_NOFS);
	error = -ENOMEM;
	if (data == NULL)
		goto out;

	error = gfs2_ea_get_copy(ip, &el, data, len);
	if (error == 0)
		error = len;
	*ppdata = data;
out:
	brelse(el.el_bh);
	return error;
}