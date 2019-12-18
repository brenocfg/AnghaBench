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
struct TYPE_2__ {scalar_t__ nrpages; } ;
struct inode {TYPE_1__ i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 int /*<<< orphan*/  generic_detach_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_inode (struct inode*) ; 

__attribute__((used)) static void generic_forget_inode(struct inode *inode)
{
	if (!generic_detach_inode(inode))
		return;
	if (inode->i_data.nrpages)
		truncate_inode_pages(&inode->i_data, 0);
	clear_inode(inode);
	wake_up_inode(inode);
	destroy_inode(inode);
}