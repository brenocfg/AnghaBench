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
 scalar_t__ SOFT_FAULT ; 
 char* memblock ; 
 char* memblock_share ; 
 size_t num_pages ; 
 scalar_t__ num_threads ; 
 size_t pgsize ; 
 scalar_t__ test_type ; 

__attribute__((used)) static void fault_pages(int thread_id)
{
	size_t region_len, region_start, region_end;
	char *ptr, *block;
	volatile char val;

	region_len = num_pages / (size_t)num_threads;
	region_start = region_len * (size_t)thread_id;

	if((size_t)thread_id < num_pages % (size_t)num_threads) {
		region_start += (size_t)thread_id;
		region_len++;
	}
	else {
		region_start += num_pages % (size_t)num_threads;
	}

	region_start *= pgsize;
	region_len *= pgsize;
	region_end = region_start + region_len;

	block = (test_type == SOFT_FAULT)? memblock_share: memblock;
	for(ptr = block + region_start; ptr < block + region_end; ptr += pgsize) {
		val = *ptr;
	}
}