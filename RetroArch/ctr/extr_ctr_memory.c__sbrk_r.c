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
typedef  int u32 ;
struct _reent {int /*<<< orphan*/  _errno; } ;
typedef  int ptrdiff_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MEMOP_ALLOC ; 
 int /*<<< orphan*/  MEMOP_FREE ; 
 int MEMPERM_READ ; 
 int MEMPERM_WRITE ; 
 int __heapBase ; 
 int __heap_size ; 
 int /*<<< orphan*/  ctr_request_free_pages (int) ; 
 scalar_t__ svcControlMemory (int*,int,int,int,int /*<<< orphan*/ ,int) ; 

void* _sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
   static u32 sbrk_top = 0;

   if (!sbrk_top)
      sbrk_top = __heapBase;

   u32 tmp;

   int diff = ((sbrk_top + incr + 0xFFF) & ~0xFFF)
      - (__heapBase + __heap_size);

   if (diff > 0)
   {
      ctr_request_free_pages(diff >> 12);

      if (svcControlMemory(&tmp, __heapBase + __heap_size,
               0x0, diff, MEMOP_ALLOC, MEMPERM_READ | MEMPERM_WRITE) < 0)
      {
         ptr->_errno = ENOMEM;
         return (caddr_t) -1;
      }
   }

   __heap_size += diff;

   if (diff < 0)
      svcControlMemory(&tmp, __heapBase + __heap_size,
            0x0, -diff, MEMOP_FREE, MEMPERM_READ | MEMPERM_WRITE);

   sbrk_top += incr;

   return (caddr_t)(sbrk_top - incr);
}