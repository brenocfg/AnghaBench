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
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFS2_EATYPE_SECURITY ; 
 int gfs2_xattr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int security_inode_init_security (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,void**,size_t*) ; 

__attribute__((used)) static int gfs2_security_init(struct gfs2_inode *dip, struct gfs2_inode *ip)
{
	int err;
	size_t len;
	void *value;
	char *name;

	err = security_inode_init_security(&ip->i_inode, &dip->i_inode,
					   &name, &value, &len);

	if (err) {
		if (err == -EOPNOTSUPP)
			return 0;
		return err;
	}

	err = gfs2_xattr_set(&ip->i_inode, GFS2_EATYPE_SECURITY, name, value, len, 0);
	kfree(value);
	kfree(name);

	return err;
}