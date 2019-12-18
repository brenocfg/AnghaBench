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
typedef  int uint ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int befs_off_t ;
typedef  int /*<<< orphan*/  befs_data_stream ;
typedef  int befs_blocknr_t ;
typedef  int /*<<< orphan*/  befs_block_run ;
struct TYPE_2__ {int block_shift; } ;

/* Variables and functions */
 scalar_t__ BEFS_OK ; 
 TYPE_1__* BEFS_SB (struct super_block*) ; 
 struct buffer_head* befs_bread_iaddr (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,int) ; 
 scalar_t__ befs_fblock2brun (struct super_block*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

struct buffer_head *
befs_read_datastream(struct super_block *sb, befs_data_stream * ds,
		     befs_off_t pos, uint * off)
{
	struct buffer_head *bh = NULL;
	befs_block_run run;
	befs_blocknr_t block;	/* block coresponding to pos */

	befs_debug(sb, "---> befs_read_datastream() %Lu", pos);
	block = pos >> BEFS_SB(sb)->block_shift;
	if (off)
		*off = pos - (block << BEFS_SB(sb)->block_shift);

	if (befs_fblock2brun(sb, ds, block, &run) != BEFS_OK) {
		befs_error(sb, "BeFS: Error finding disk addr of block %lu",
			   block);
		befs_debug(sb, "<--- befs_read_datastream() ERROR");
		return NULL;
	}
	bh = befs_bread_iaddr(sb, run);
	if (!bh) {
		befs_error(sb, "BeFS: Error reading block %lu from datastream",
			   block);
		return NULL;
	}

	befs_debug(sb, "<--- befs_read_datastream() read data, starting at %Lu",
		   pos);

	return bh;
}