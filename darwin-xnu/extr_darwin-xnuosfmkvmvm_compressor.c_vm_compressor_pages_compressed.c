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
 int PAGE_SIZE_64 ; 
 int c_segment_pages_compressed ; 

uint64_t
vm_compressor_pages_compressed(void)
{
	return (c_segment_pages_compressed * PAGE_SIZE_64);
}