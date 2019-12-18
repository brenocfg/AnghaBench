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
struct writeback_control {int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int filemap_fdatawrite (struct address_space*) ; 
 int sync_inode (struct inode*,struct writeback_control*) ; 

__attribute__((used)) static int writeback_inode(struct inode *inode)
{

	int ret;
	struct address_space *mapping = inode->i_mapping;
	struct writeback_control wbc = {
	       .sync_mode = WB_SYNC_NONE,
	      .nr_to_write = 0,
	};
	/* if we used WB_SYNC_ALL, sync_inode waits for the io for the
	* inode to finish.  So WB_SYNC_NONE is sent down to sync_inode
	* and filemap_fdatawrite is used for the data blocks
	*/
	ret = sync_inode(inode, &wbc);
	if (!ret)
	       ret = filemap_fdatawrite(mapping);
	return ret;
}