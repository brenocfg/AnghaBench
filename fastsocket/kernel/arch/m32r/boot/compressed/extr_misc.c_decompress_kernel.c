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
 scalar_t__ BOOT_HEAP_SIZE ; 
 scalar_t__ CONFIG_MEMORY_START ; 
 int /*<<< orphan*/  decompress (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error ; 
 scalar_t__ free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 int /*<<< orphan*/  puts (char*) ; 

void
decompress_kernel(int mmu_on, unsigned char *zimage_data,
		  unsigned int zimage_len, unsigned long heap)
{
	unsigned char *input_data = zimage_data;
	int input_len = zimage_len;
	unsigned char *output_data;

	output_data = (unsigned char *)CONFIG_MEMORY_START + 0x2000
		+ (mmu_on ? 0x80000000 : 0);
	free_mem_ptr = heap;
	free_mem_end_ptr = free_mem_ptr + BOOT_HEAP_SIZE;

	puts("\nDecompressing Linux... ");
	decompress(input_data, input_len, NULL, NULL, output_data, NULL, error);
	puts("done.\nBooting the kernel.\n");
}