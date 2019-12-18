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
 int /*<<< orphan*/  mem1_heap ; 

void * MEM1_alloc(unsigned int size, unsigned int align)
{
   if (align < 4)
      align = 4;
   return MEMAllocFromExpHeapEx(mem1_heap, size, align);
}