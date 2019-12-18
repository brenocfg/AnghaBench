#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode_smack {char* smk_inode; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {char* smk_known; } ;
struct TYPE_3__ {struct inode_smack* i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  XATTR_NAME_SMACK ; 
 TYPE_2__ smack_known_invalid ; 
 char* smk_import (void const*,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smack_inode_post_setxattr(struct dentry *dentry, const char *name,
				      const void *value, size_t size, int flags)
{
	struct inode_smack *isp;
	char *nsp;

	/*
	 * Not SMACK
	 */
	if (strcmp(name, XATTR_NAME_SMACK))
		return;

	isp = dentry->d_inode->i_security;

	/*
	 * No locking is done here. This is a pointer
	 * assignment.
	 */
	nsp = smk_import(value, size);
	if (nsp != NULL)
		isp->smk_inode = nsp;
	else
		isp->smk_inode = smack_known_invalid.smk_known;

	return;
}