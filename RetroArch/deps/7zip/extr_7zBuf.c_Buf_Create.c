#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {scalar_t__ (* Alloc ) (TYPE_1__*,size_t) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CBuf ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*,size_t) ; 

int Buf_Create(CBuf *p, size_t size, ISzAlloc *alloc)
{
   p->size = 0;
   if (size == 0)
   {
      p->data = 0;
      return 1;
   }
   p->data = (uint8_t *)alloc->Alloc(alloc, size);
   if (p->data != 0)
   {
      p->size = size;
      return 1;
   }
   return 0;
}