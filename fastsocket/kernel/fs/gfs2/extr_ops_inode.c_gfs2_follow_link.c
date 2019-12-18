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
struct nameidata {int /*<<< orphan*/  path; } ;
struct gfs2_inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 int GFS2_FAST_NAME_SIZE ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int gfs2_readlinki (struct gfs2_inode*,char**,unsigned int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int vfs_follow_link (struct nameidata*,char*) ; 

__attribute__((used)) static void *gfs2_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct gfs2_inode *ip = GFS2_I(dentry->d_inode);
	char array[GFS2_FAST_NAME_SIZE], *buf = array;
	unsigned int len = GFS2_FAST_NAME_SIZE;
	int error;

	error = gfs2_readlinki(ip, &buf, &len);
	if (!error) {
		error = vfs_follow_link(nd, buf);
		if (buf != array)
			kfree(buf);
	} else
		path_put(&nd->path);

	return ERR_PTR(error);
}