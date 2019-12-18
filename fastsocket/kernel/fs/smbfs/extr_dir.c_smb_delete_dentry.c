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
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_bad_inode (scalar_t__) ; 

__attribute__((used)) static int
smb_delete_dentry(struct dentry * dentry)
{
	if (dentry->d_inode) {
		if (is_bad_inode(dentry->d_inode)) {
			PARANOIA("bad inode, unhashing %s/%s\n",
				 DENTRY_PATH(dentry));
			return 1;
		}
	} else {
		/* N.B. Unhash negative dentries? */
	}
	return 0;
}