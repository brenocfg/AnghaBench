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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int /*<<< orphan*/  file_mask_to_av (int /*<<< orphan*/ ,int) ; 
 int inode_has_perm (struct cred const*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_inode_permission(struct inode *inode, int mask)
{
	const struct cred *cred = current_cred();

	if (!mask) {
		/* No permission to check.  Existence test. */
		return 0;
	}

	return inode_has_perm(cred, inode,
			      file_mask_to_av(inode->i_mode, mask), NULL);
}