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
typedef  int uint32_t ;

/* Variables and functions */
 size_t __lwp_heap_block_size (int /*<<< orphan*/ *,void*) ; 
 size_t __real_malloc_usable_size (void*) ; 
 int /*<<< orphan*/  gx_mem2_heap ; 

__attribute__ ((used)) size_t __wrap_malloc_usable_size(void *p)
{
   if (((uint32_t) p & 0x10000000) != 0)
      return __lwp_heap_block_size(&gx_mem2_heap, p);
   return __real_malloc_usable_size(p);
}