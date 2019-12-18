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

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_WIMG_IO ; 
 int /*<<< orphan*/  cfgAdr ; 
 int cfgDat ; 
 int inl (int) ; 
 scalar_t__ io_map_spec (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,unsigned long,int) ; 
 int lpcCfg ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rcbaArea ; 
 int rcbaAreap ; 

__attribute__((used)) static void
map_rcbaArea(void)
{
	/*
	 * Get RCBA area physical address and map it
	 */
	outl(cfgAdr, lpcCfg | (0xF0 & 0xFC));
	rcbaAreap = inl(cfgDat | (0xF0 & 0x03));
	rcbaArea = io_map_spec(rcbaAreap & -4096, PAGE_SIZE * 4, VM_WIMG_IO);
	kprintf("RCBA: vaddr = %lX, paddr = %08X\n", (unsigned long)rcbaArea, rcbaAreap);
}