#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* getxattr ) (struct dentry*,int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int SMK_LABELLEN ; 
 int /*<<< orphan*/  XATTR_NAME_SMACK ; 
 char* smk_import (char*,int) ; 
 int stub1 (struct dentry*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *smk_fetch(struct inode *ip, struct dentry *dp)
{
	int rc;
	char in[SMK_LABELLEN];

	if (ip->i_op->getxattr == NULL)
		return NULL;

	rc = ip->i_op->getxattr(dp, XATTR_NAME_SMACK, in, SMK_LABELLEN);
	if (rc < 0)
		return NULL;

	return smk_import(in, rc);
}