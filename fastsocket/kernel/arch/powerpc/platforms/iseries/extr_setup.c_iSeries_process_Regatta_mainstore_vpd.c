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
typedef  int u32 ;
struct MemoryBlock {unsigned long absStart; unsigned long absEnd; unsigned long logicalStart; unsigned long logicalEnd; } ;
struct IoHriMainStoreSegment5 {int msAreaExists; struct IoHriMainStoreArea4* msAreaArray; } ;
struct IoHriMainStoreArea4 {unsigned long numAdrRangeBlocks; TYPE_1__* xAdrRangeBlock; } ;
struct TYPE_2__ {scalar_t__ blockEnd; scalar_t__ blockStart; } ;

/* Variables and functions */
 unsigned long MaxSegmentAreas ; 
 void* addr_to_chunk (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ xMsVpd ; 

__attribute__((used)) static unsigned long iSeries_process_Regatta_mainstore_vpd(
		struct MemoryBlock *mb_array, unsigned long max_entries)
{
	struct IoHriMainStoreSegment5 *msVpdP =
		(struct IoHriMainStoreSegment5 *)xMsVpd;
	unsigned long numSegmentBlocks = 0;
	u32 existsBits = msVpdP->msAreaExists;
	unsigned long area_num;

	printk("Mainstore_VPD: Regatta\n");

	for (area_num = 0; area_num < MaxSegmentAreas; ++area_num ) {
		unsigned long numAreaBlocks;
		struct IoHriMainStoreArea4 *currentArea;

		if (existsBits & 0x80000000) {
			unsigned long block_num;

			currentArea = &msVpdP->msAreaArray[area_num];
			numAreaBlocks = currentArea->numAdrRangeBlocks;
			printk("ms_vpd: processing area %2ld  blocks=%ld",
					area_num, numAreaBlocks);
			for (block_num = 0; block_num < numAreaBlocks;
					++block_num ) {
				/* Process an address range block */
				struct MemoryBlock tempBlock;
				unsigned long i;

				tempBlock.absStart =
					(unsigned long)currentArea->xAdrRangeBlock[block_num].blockStart;
				tempBlock.absEnd =
					(unsigned long)currentArea->xAdrRangeBlock[block_num].blockEnd;
				tempBlock.logicalStart = 0;
				tempBlock.logicalEnd   = 0;
				printk("\n          block %ld absStart=%016lx absEnd=%016lx",
						block_num, tempBlock.absStart,
						tempBlock.absEnd);

				for (i = 0; i < numSegmentBlocks; ++i) {
					if (mb_array[i].absStart ==
							tempBlock.absStart)
						break;
				}
				if (i == numSegmentBlocks) {
					if (numSegmentBlocks == max_entries)
						panic("iSeries_process_mainstore_vpd: too many memory blocks");
					mb_array[numSegmentBlocks] = tempBlock;
					++numSegmentBlocks;
				} else
					printk(" (duplicate)");
			}
			printk("\n");
		}
		existsBits <<= 1;
	}
	/* Now sort the blocks found into ascending sequence */
	if (numSegmentBlocks > 1) {
		unsigned long m, n;

		for (m = 0; m < numSegmentBlocks - 1; ++m) {
			for (n = numSegmentBlocks - 1; m < n; --n) {
				if (mb_array[n].absStart <
						mb_array[n-1].absStart) {
					struct MemoryBlock tempBlock;

					tempBlock = mb_array[n];
					mb_array[n] = mb_array[n-1];
					mb_array[n-1] = tempBlock;
				}
			}
		}
	}
	/*
	 * Assign "logical" addresses to each block.  These
	 * addresses correspond to the hypervisor "bitmap" space.
	 * Convert all addresses into units of 256K chunks.
	 */
	{
	unsigned long i, nextBitmapAddress;

	printk("ms_vpd: %ld sorted memory blocks\n", numSegmentBlocks);
	nextBitmapAddress = 0;
	for (i = 0; i < numSegmentBlocks; ++i) {
		unsigned long length = mb_array[i].absEnd -
			mb_array[i].absStart;

		mb_array[i].logicalStart = nextBitmapAddress;
		mb_array[i].logicalEnd = nextBitmapAddress + length;
		nextBitmapAddress += length;
		printk("          Bitmap range: %016lx - %016lx\n"
				"        Absolute range: %016lx - %016lx\n",
				mb_array[i].logicalStart,
				mb_array[i].logicalEnd,
				mb_array[i].absStart, mb_array[i].absEnd);
		mb_array[i].absStart = addr_to_chunk(mb_array[i].absStart &
				0x000fffffffffffffUL);
		mb_array[i].absEnd = addr_to_chunk(mb_array[i].absEnd &
				0x000fffffffffffffUL);
		mb_array[i].logicalStart =
			addr_to_chunk(mb_array[i].logicalStart);
		mb_array[i].logicalEnd = addr_to_chunk(mb_array[i].logicalEnd);
	}
	}

	return numSegmentBlocks;
}