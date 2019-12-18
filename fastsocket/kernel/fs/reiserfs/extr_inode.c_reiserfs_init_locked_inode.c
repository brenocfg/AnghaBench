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
struct reiserfs_iget_args {int /*<<< orphan*/  dirid; int /*<<< orphan*/  objectid; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int reiserfs_init_locked_inode(struct inode *inode, void *p)
{
	struct reiserfs_iget_args *args = (struct reiserfs_iget_args *)p;
	inode->i_ino = args->objectid;
	INODE_PKEY(inode)->k_dir_id = cpu_to_le32(args->dirid);
	return 0;
}