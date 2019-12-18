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
typedef  int uint32_t ;
struct jffs2_sb_info {int resv_blocks_deletion; int flash_size; int nr_blocks; int sector_size; int resv_blocks_write; int resv_blocks_gctrigger; int resv_blocks_gcmerge; int resv_blocks_gcbad; int vdirty_blocks_gctrigger; int nospc_dirty_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_fsbuild (char*,int,...) ; 
 scalar_t__ jffs2_can_mark_obsolete (struct jffs2_sb_info*) ; 

__attribute__((used)) static void jffs2_calc_trigger_levels(struct jffs2_sb_info *c)
{
	uint32_t size;

	/* Deletion should almost _always_ be allowed. We're fairly
	   buggered once we stop allowing people to delete stuff
	   because there's not enough free space... */
	c->resv_blocks_deletion = 2;

	/* Be conservative about how much space we need before we allow writes.
	   On top of that which is required for deletia, require an extra 2%
	   of the medium to be available, for overhead caused by nodes being
	   split across blocks, etc. */

	size = c->flash_size / 50; /* 2% of flash size */
	size += c->nr_blocks * 100; /* And 100 bytes per eraseblock */
	size += c->sector_size - 1; /* ... and round up */

	c->resv_blocks_write = c->resv_blocks_deletion + (size / c->sector_size);

	/* When do we let the GC thread run in the background */

	c->resv_blocks_gctrigger = c->resv_blocks_write + 1;

	/* When do we allow garbage collection to merge nodes to make
	   long-term progress at the expense of short-term space exhaustion? */
	c->resv_blocks_gcmerge = c->resv_blocks_deletion + 1;

	/* When do we allow garbage collection to eat from bad blocks rather
	   than actually making progress? */
	c->resv_blocks_gcbad = 0;//c->resv_blocks_deletion + 2;

	/* What number of 'very dirty' eraseblocks do we allow before we
	   trigger the GC thread even if we don't _need_ the space. When we
	   can't mark nodes obsolete on the medium, the old dirty nodes cause
	   performance problems because we have to inspect and discard them. */
	c->vdirty_blocks_gctrigger = c->resv_blocks_gctrigger;
	if (jffs2_can_mark_obsolete(c))
		c->vdirty_blocks_gctrigger *= 10;

	/* If there's less than this amount of dirty space, don't bother
	   trying to GC to make more space. It'll be a fruitless task */
	c->nospc_dirty_size = c->sector_size + (c->flash_size / 100);

	dbg_fsbuild("JFFS2 trigger levels (size %d KiB, block size %d KiB, %d blocks)\n",
		  c->flash_size / 1024, c->sector_size / 1024, c->nr_blocks);
	dbg_fsbuild("Blocks required to allow deletion:    %d (%d KiB)\n",
		  c->resv_blocks_deletion, c->resv_blocks_deletion*c->sector_size/1024);
	dbg_fsbuild("Blocks required to allow writes:      %d (%d KiB)\n",
		  c->resv_blocks_write, c->resv_blocks_write*c->sector_size/1024);
	dbg_fsbuild("Blocks required to quiesce GC thread: %d (%d KiB)\n",
		  c->resv_blocks_gctrigger, c->resv_blocks_gctrigger*c->sector_size/1024);
	dbg_fsbuild("Blocks required to allow GC merges:   %d (%d KiB)\n",
		  c->resv_blocks_gcmerge, c->resv_blocks_gcmerge*c->sector_size/1024);
	dbg_fsbuild("Blocks required to GC bad blocks:     %d (%d KiB)\n",
		  c->resv_blocks_gcbad, c->resv_blocks_gcbad*c->sector_size/1024);
	dbg_fsbuild("Amount of dirty space required to GC: %d bytes\n",
		  c->nospc_dirty_size);
	dbg_fsbuild("Very dirty blocks before GC triggered: %d\n",
		  c->vdirty_blocks_gctrigger);
}