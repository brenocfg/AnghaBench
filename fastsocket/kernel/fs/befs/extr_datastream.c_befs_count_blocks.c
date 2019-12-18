#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct super_block {int dummy; } ;
struct TYPE_9__ {int block_shift; int block_size; } ;
typedef  TYPE_3__ befs_sb_info ;
struct TYPE_8__ {scalar_t__ len; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_10__ {int size; int max_direct_range; int max_indirect_range; int max_double_indirect_range; TYPE_2__ double_indirect; TYPE_1__ indirect; } ;
typedef  TYPE_4__ befs_data_stream ;
typedef  int befs_blocknr_t ;

/* Variables and functions */
 int BEFS_DBLINDIR_BRUN_LEN ; 
 TYPE_3__* BEFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int befs_iaddrs_per_block (struct super_block*) ; 

befs_blocknr_t
befs_count_blocks(struct super_block * sb, befs_data_stream * ds)
{
	befs_blocknr_t blocks;
	befs_blocknr_t datablocks;	/* File data blocks */
	befs_blocknr_t metablocks;	/* FS metadata blocks */
	befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> befs_count_blocks()");

	datablocks = ds->size >> befs_sb->block_shift;
	if (ds->size & (befs_sb->block_size - 1))
		datablocks += 1;

	metablocks = 1;		/* Start with 1 block for inode */

	/* Size of indirect block */
	if (ds->size > ds->max_direct_range)
		metablocks += ds->indirect.len;

	/*
	   Double indir block, plus all the indirect blocks it mapps
	   In the double-indirect range, all block runs of data are
	   BEFS_DBLINDIR_BRUN_LEN blocks long. Therefore, we know 
	   how many data block runs are in the double-indirect region,
	   and from that we know how many indirect blocks it takes to
	   map them. We assume that the indirect blocks are also
	   BEFS_DBLINDIR_BRUN_LEN blocks long.
	 */
	if (ds->size > ds->max_indirect_range && ds->max_indirect_range != 0) {
		uint dbl_bytes;
		uint dbl_bruns;
		uint indirblocks;

		dbl_bytes =
		    ds->max_double_indirect_range - ds->max_indirect_range;
		dbl_bruns =
		    dbl_bytes / (befs_sb->block_size * BEFS_DBLINDIR_BRUN_LEN);
		indirblocks = dbl_bruns / befs_iaddrs_per_block(sb);

		metablocks += ds->double_indirect.len;
		metablocks += indirblocks;
	}

	blocks = datablocks + metablocks;
	befs_debug(sb, "<--- befs_count_blocks() %u blocks", blocks);

	return blocks;
}