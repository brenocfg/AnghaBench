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
 void* MEMAllocFromExpHeapEx (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  MEMGetBaseHeapHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_BASE_HEAP_MEM2 ; 

void * MEM2_alloc(unsigned int size, unsigned int align)
{
   return MEMAllocFromExpHeapEx(MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), size, align);
}