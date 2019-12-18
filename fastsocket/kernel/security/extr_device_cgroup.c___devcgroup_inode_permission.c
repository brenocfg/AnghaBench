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

/* Variables and functions */
 short ACC_READ ; 
 short ACC_WRITE ; 
 short DEV_BLOCK ; 
 short DEV_CHAR ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int __devcgroup_check_permission (short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 

int __devcgroup_inode_permission(struct inode *inode, int mask)
{
	short type, access = 0;

	if (S_ISBLK(inode->i_mode))
		type = DEV_BLOCK;
	if (S_ISCHR(inode->i_mode))
		type = DEV_CHAR;
	if (mask & MAY_WRITE)
		access |= ACC_WRITE;
	if (mask & MAY_READ)
		access |= ACC_READ;

	return __devcgroup_check_permission(type, imajor(inode), iminor(inode),
			access);
}