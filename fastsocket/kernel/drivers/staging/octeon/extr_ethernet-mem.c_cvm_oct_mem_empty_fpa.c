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
 scalar_t__ USE_SKBUFFS_IN_HW ; 
 int /*<<< orphan*/  cvm_oct_free_hw_memory (int,int,int) ; 
 int /*<<< orphan*/  cvm_oct_free_hw_skbuff (int,int,int) ; 

void cvm_oct_mem_empty_fpa(int pool, int size, int elements)
{
	if (USE_SKBUFFS_IN_HW)
		cvm_oct_free_hw_skbuff(pool, size, elements);
	else
		cvm_oct_free_hw_memory(pool, size, elements);
}