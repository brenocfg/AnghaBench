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
 scalar_t__ HEAP_SIZE ; 
 int /*<<< orphan*/  _end ; 
 scalar_t__ free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 int /*<<< orphan*/  gunzip () ; 
 int /*<<< orphan*/  makecrc () ; 
 scalar_t__ output_data ; 
 unsigned long output_ptr ; 
 int /*<<< orphan*/  puts (char*) ; 

void decompress_kernel(void)
{
	output_data = 0;
	output_ptr = (unsigned long)0x400000;
	free_mem_ptr = (unsigned long)&_end;
	free_mem_end_ptr = free_mem_ptr + HEAP_SIZE;

	makecrc();
	puts("Uncompressing Linux... ");
	gunzip();
	puts("Ok, booting the kernel.\n");
}