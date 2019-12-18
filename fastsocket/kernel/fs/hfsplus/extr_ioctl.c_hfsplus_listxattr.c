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
struct dentry {struct inode* d_inode; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EOPNOTSUPP ; 
 size_t ERANGE ; 
 size_t HFSPLUS_ATTRLIST_SIZE ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

ssize_t hfsplus_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	struct inode *inode = dentry->d_inode;

	if (!S_ISREG(inode->i_mode) || HFSPLUS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	if (!buffer || !size)
		return HFSPLUS_ATTRLIST_SIZE;
	if (size < HFSPLUS_ATTRLIST_SIZE)
		return -ERANGE;
	strcpy(buffer, "hfs.type");
	strcpy(buffer + sizeof("hfs.type"), "hfs.creator");

	return HFSPLUS_ATTRLIST_SIZE;
}