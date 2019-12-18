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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ FIFO_REALLOC_MEM_SIZE ; 
 scalar_t__ fifo_current_realloc_mem_size ; 

void SetFifoCurrentReallocMemSize(UINT size)
{
	if (size == 0)
	{
		size = FIFO_REALLOC_MEM_SIZE;
	}

	fifo_current_realloc_mem_size = size;
}