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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 void* __lwp_heap_allocate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gx_mem2_heap ; 

void *_mem2_memalign(uint8_t align, uint32_t size)
{
   if(size == 0)
      return NULL;
   return __lwp_heap_allocate(&gx_mem2_heap, size);
}