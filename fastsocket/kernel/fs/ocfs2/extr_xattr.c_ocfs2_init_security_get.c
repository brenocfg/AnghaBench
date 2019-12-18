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
struct ocfs2_security_xattr_info {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_supports_xattr (int /*<<< orphan*/ ) ; 
 int security_inode_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ocfs2_init_security_get(struct inode *inode,
			    struct inode *dir,
			    struct ocfs2_security_xattr_info *si)
{
	/* check whether ocfs2 support feature xattr */
	if (!ocfs2_supports_xattr(OCFS2_SB(dir->i_sb)))
		return -EOPNOTSUPP;
	return security_inode_init_security(inode, dir, &si->name, &si->value,
					    &si->value_len);
}