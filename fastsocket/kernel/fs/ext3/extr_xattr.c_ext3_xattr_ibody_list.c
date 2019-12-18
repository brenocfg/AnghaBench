#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext3_xattr_ibody_header {int dummy; } ;
struct ext3_inode {int dummy; } ;
struct ext3_iloc {int /*<<< orphan*/  bh; } ;
struct TYPE_4__ {int i_state; } ;
struct TYPE_3__ {int s_inode_size; } ;

/* Variables and functions */
 TYPE_2__* EXT3_I (struct inode*) ; 
 TYPE_1__* EXT3_SB (int /*<<< orphan*/ ) ; 
 int EXT3_STATE_XATTR ; 
 int /*<<< orphan*/  IFIRST (struct ext3_xattr_ibody_header*) ; 
 struct ext3_xattr_ibody_header* IHDR (struct inode*,struct ext3_inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int ext3_get_inode_loc (struct inode*,struct ext3_iloc*) ; 
 struct ext3_inode* ext3_raw_inode (struct ext3_iloc*) ; 
 int ext3_xattr_check_names (int /*<<< orphan*/ ,void*) ; 
 int ext3_xattr_list_entries (struct inode*,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
ext3_xattr_ibody_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	struct ext3_xattr_ibody_header *header;
	struct ext3_inode *raw_inode;
	struct ext3_iloc iloc;
	void *end;
	int error;

	if (!(EXT3_I(inode)->i_state & EXT3_STATE_XATTR))
		return 0;
	error = ext3_get_inode_loc(inode, &iloc);
	if (error)
		return error;
	raw_inode = ext3_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	end = (void *)raw_inode + EXT3_SB(inode->i_sb)->s_inode_size;
	error = ext3_xattr_check_names(IFIRST(header), end);
	if (error)
		goto cleanup;
	error = ext3_xattr_list_entries(inode, IFIRST(header),
					buffer, buffer_size);

cleanup:
	brelse(iloc.bh);
	return error;
}