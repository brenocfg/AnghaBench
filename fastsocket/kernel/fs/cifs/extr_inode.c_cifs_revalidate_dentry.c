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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {scalar_t__ invalid_mapping; } ;

/* Variables and functions */
 TYPE_1__* CIFS_I (struct inode*) ; 
 int cifs_invalidate_mapping (struct inode*) ; 
 int cifs_revalidate_dentry_attr (struct dentry*) ; 

int cifs_revalidate_dentry(struct dentry *dentry)
{
	int rc;
	struct inode *inode = dentry->d_inode;

	rc = cifs_revalidate_dentry_attr(dentry);
	if (rc)
		return rc;

	if (CIFS_I(inode)->invalid_mapping)
		rc = cifs_invalidate_mapping(inode);
	return rc;
}