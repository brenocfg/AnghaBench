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
typedef  int u64 ;
typedef  int s64 ;

/* Variables and functions */
 int BIOS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  UV_BIOS_WATCHLIST_ALLOC ; 
 scalar_t__ uv_bios_call_irqsave (int /*<<< orphan*/ ,unsigned long,unsigned int,int,int,int /*<<< orphan*/ ) ; 

int
uv_bios_mq_watchlist_alloc(unsigned long addr, unsigned int mq_size,
			   unsigned long *intr_mmr_offset)
{
	u64 watchlist;
	s64 ret;

	/*
	 * bios returns watchlist number or negative error number.
	 */
	ret = (int)uv_bios_call_irqsave(UV_BIOS_WATCHLIST_ALLOC, addr,
			mq_size, (u64)intr_mmr_offset,
			(u64)&watchlist, 0);
	if (ret < BIOS_STATUS_SUCCESS)
		return ret;

	return watchlist;
}