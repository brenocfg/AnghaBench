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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 unsigned long long NEXT_OFFSET ; 
 unsigned long long cvmx_read64_uint64 (unsigned long long) ; 

__attribute__((used)) static uint64_t cvmx_bootmem_phy_get_next(uint64_t addr)
{
	return cvmx_read64_uint64((addr + NEXT_OFFSET) | (1ull << 63));
}