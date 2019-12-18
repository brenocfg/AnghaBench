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
typedef  int uint64_t ;

/* Variables and functions */
 int COMPRESSED_SWAP_CHUNK_SIZE ; 
 scalar_t__ vm_swapfile_total_segs_alloced ; 

uint64_t
vm_swap_get_total_space(void)
{
	uint64_t total_space = 0;

	total_space = (uint64_t)vm_swapfile_total_segs_alloced * COMPRESSED_SWAP_CHUNK_SIZE;

	return total_space;
}