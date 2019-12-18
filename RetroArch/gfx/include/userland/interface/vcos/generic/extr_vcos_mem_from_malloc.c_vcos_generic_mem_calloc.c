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
typedef  int VCOS_UNSIGNED ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_ALIGN ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* vcos_generic_mem_alloc_aligned (int,int /*<<< orphan*/ ,char const*) ; 

void *vcos_generic_mem_calloc(VCOS_UNSIGNED count, VCOS_UNSIGNED sz, const char *desc)
{
   uint32_t size = count*sz;
   void *ptr = vcos_generic_mem_alloc_aligned(size,MIN_ALIGN,desc);
   if (ptr)
   {
      memset(ptr, 0, size);
   }
   return ptr;
}