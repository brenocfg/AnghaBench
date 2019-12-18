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
struct inode {int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 TYPE_1__* HOSTFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  close_file (int*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostfs_delete_inode(struct inode *inode)
{
	truncate_inode_pages(&inode->i_data, 0);
	if (HOSTFS_I(inode)->fd != -1) {
		close_file(&HOSTFS_I(inode)->fd);
		HOSTFS_I(inode)->fd = -1;
	}
	clear_inode(inode);
}