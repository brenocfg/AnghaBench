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
 int /*<<< orphan*/  __real_free (void*) ; 
 void* __real_malloc (size_t) ; 
 size_t __real_malloc_usable_size (void*) ; 
 void* __real_realloc (void*,size_t) ; 
 int /*<<< orphan*/  _mem2_free (void*) ; 
 void* _mem2_malloc (size_t) ; 
 void* _mem2_realloc (void*,size_t) ; 
 int /*<<< orphan*/  gx_mem2_heap ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__ ((used)) void *__wrap_realloc(void *p, size_t size)
{
   void *n;
   /* ptr from mem2 */
   if (((uint32_t) p & 0x10000000) != 0)
   {
      n = _mem2_realloc(p, size);
      if (n != 0)
         return n;
      n = __real_malloc(size);
      if (n == 0)
         return 0;
      if (p != 0)
      {
         size_t heap_size = __lwp_heap_block_size(&gx_mem2_heap, p);
         memcpy(n, p, heap_size < size ? heap_size : size);
         _mem2_free(p);
      }
      return n;
   }
   /* ptr from malloc */
   n = __real_realloc(p, size);
   if (n != 0)
      return n;
   n = _mem2_malloc(size);
   if (n == 0)
      return 0;
   if (p != 0)
   {
      size_t heap_size = __real_malloc_usable_size(p);
      memcpy(n, p, heap_size < size ? heap_size : size);
      __real_free(p);
   }
   return n;
}