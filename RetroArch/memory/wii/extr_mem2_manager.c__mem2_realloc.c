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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ __lwp_heap_block_size (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  _mem2_free (void*) ; 
 void* _mem2_malloc (scalar_t__) ; 
 int /*<<< orphan*/  gx_mem2_heap ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 

void *_mem2_realloc(void *ptr, uint32_t newsize)
{
   uint32_t size;
   void *newptr = NULL;

   if (!ptr)
      return _mem2_malloc(newsize);

   if (newsize == 0)
   {
      _mem2_free(ptr);
      return NULL;
   }

   size = __lwp_heap_block_size(&gx_mem2_heap, ptr);

   if (size > newsize)
      size = newsize;

   newptr = _mem2_malloc(newsize);

   if (!newptr)
      return NULL;

   memcpy(newptr, ptr, size);
   _mem2_free(ptr);

   return newptr;
}