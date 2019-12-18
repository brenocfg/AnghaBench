#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_6__ {scalar_t__ num_ags; } ;
typedef  TYPE_1__ befs_sb_info ;
struct TYPE_7__ {scalar_t__ allocation_group; int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ befs_inode_addr ;
typedef  int /*<<< orphan*/  befs_blocknr_t ;

/* Variables and functions */
 TYPE_1__* BEFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  iaddr2blockno (struct super_block*,TYPE_2__*) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 

struct buffer_head *
befs_bread_iaddr(struct super_block *sb, befs_inode_addr iaddr)
{
	struct buffer_head *bh = NULL;
	befs_blocknr_t block = 0;
	befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> Enter befs_read_iaddr() "
		   "[%u, %hu, %hu]",
		   iaddr.allocation_group, iaddr.start, iaddr.len);

	if (iaddr.allocation_group > befs_sb->num_ags) {
		befs_error(sb, "BEFS: Invalid allocation group %u, max is %u",
			   iaddr.allocation_group, befs_sb->num_ags);
		goto error;
	}

	block = iaddr2blockno(sb, &iaddr);

	befs_debug(sb, "befs_read_iaddr: offset = %lu", block);

	bh = sb_bread(sb, block);

	if (bh == NULL) {
		befs_error(sb, "Failed to read block %lu", block);
		goto error;
	}

	befs_debug(sb, "<--- befs_read_iaddr()");
	return bh;

      error:
	befs_debug(sb, "<--- befs_read_iaddr() ERROR");
	return NULL;
}