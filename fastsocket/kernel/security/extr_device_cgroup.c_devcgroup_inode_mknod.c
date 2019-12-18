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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_MKNOD ; 
 short DEV_BLOCK ; 
 short DEV_CHAR ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISBLK (int) ; 
 int /*<<< orphan*/  S_ISCHR (int) ; 
 int __devcgroup_check_permission (short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int devcgroup_inode_mknod(int mode, dev_t dev)
{
	short type;

	if (!S_ISBLK(mode) && !S_ISCHR(mode))
		return 0;

	if (S_ISBLK(mode))
		type = DEV_BLOCK;
	else
		type = DEV_CHAR;

	return __devcgroup_check_permission(type, MAJOR(dev), MINOR(dev),
			ACC_MKNOD);

}