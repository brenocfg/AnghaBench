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
 int /*<<< orphan*/  CACHE_SYNC_INSTRUCTIONS ; 
 int /*<<< orphan*/  CACHE_SYNC_WRITEBACK ; 
 int /*<<< orphan*/  CacheRangeFlush (void*,int,int /*<<< orphan*/ ) ; 

void cache_flush_d_inval_i(void *start_addr, void *end_addr)
{
	int size = end_addr - start_addr;
	CacheRangeFlush(start_addr, size, CACHE_SYNC_WRITEBACK);
	CacheRangeFlush(start_addr, size, CACHE_SYNC_INSTRUCTIONS);
}