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
struct MemoryBlock {unsigned long logicalStart; int logicalEnd; unsigned long absStart; int absEnd; } ;
struct IoHriMainStoreSegment4 {unsigned long nonInterleavedBlocksStartAdr; unsigned long nonInterleavedBlocksEndAdr; } ;

/* Variables and functions */
 unsigned long addr_to_chunk (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ xMsVpd ; 

__attribute__((used)) static unsigned long iSeries_process_Condor_mainstore_vpd(
		struct MemoryBlock *mb_array, unsigned long max_entries)
{
	unsigned long holeFirstChunk, holeSizeChunks;
	unsigned long numMemoryBlocks = 1;
	struct IoHriMainStoreSegment4 *msVpd =
		(struct IoHriMainStoreSegment4 *)xMsVpd;
	unsigned long holeStart = msVpd->nonInterleavedBlocksStartAdr;
	unsigned long holeEnd = msVpd->nonInterleavedBlocksEndAdr;
	unsigned long holeSize = holeEnd - holeStart;

	printk("Mainstore_VPD: Condor\n");
	/*
	 * Determine if absolute memory has any
	 * holes so that we can interpret the
	 * access map we get back from the hypervisor
	 * correctly.
	 */
	mb_array[0].logicalStart = 0;
	mb_array[0].logicalEnd = 0x100000000UL;
	mb_array[0].absStart = 0;
	mb_array[0].absEnd = 0x100000000UL;

	if (holeSize) {
		numMemoryBlocks = 2;
		holeStart = holeStart & 0x000fffffffffffffUL;
		holeStart = addr_to_chunk(holeStart);
		holeFirstChunk = holeStart;
		holeSize = addr_to_chunk(holeSize);
		holeSizeChunks = holeSize;
		printk( "Main store hole: start chunk = %0lx, size = %0lx chunks\n",
				holeFirstChunk, holeSizeChunks );
		mb_array[0].logicalEnd = holeFirstChunk;
		mb_array[0].absEnd = holeFirstChunk;
		mb_array[1].logicalStart = holeFirstChunk;
		mb_array[1].logicalEnd = 0x100000000UL - holeSizeChunks;
		mb_array[1].absStart = holeFirstChunk + holeSizeChunks;
		mb_array[1].absEnd = 0x100000000UL;
	}
	return numMemoryBlocks;
}