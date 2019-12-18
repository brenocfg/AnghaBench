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
typedef  unsigned short u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_memcpy (unsigned long,unsigned short,unsigned long,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  blackfin_dcache_invalidate_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void _dma_in(unsigned long addr, unsigned long buf, unsigned short len,
                    u16 size, u16 dma_size)
{
	blackfin_dcache_invalidate_range(buf, buf + len * size);
	__dma_memcpy(buf, size, addr, 0, len, dma_size);
}