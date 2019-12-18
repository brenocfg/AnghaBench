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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * fscache; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_FSCACHE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_fscache_init_inode_cookie(struct inode *inode)
{
	NFS_I(inode)->fscache = NULL;
	if (S_ISREG(inode->i_mode))
		set_bit(NFS_INO_FSCACHE, &NFS_I(inode)->flags);
}