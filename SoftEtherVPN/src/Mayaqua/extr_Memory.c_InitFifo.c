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
 int /*<<< orphan*/  FIFO_REALLOC_MEM_SIZE ; 
 int /*<<< orphan*/  fifo_current_realloc_mem_size ; 

void InitFifo()
{
	fifo_current_realloc_mem_size = FIFO_REALLOC_MEM_SIZE;
}