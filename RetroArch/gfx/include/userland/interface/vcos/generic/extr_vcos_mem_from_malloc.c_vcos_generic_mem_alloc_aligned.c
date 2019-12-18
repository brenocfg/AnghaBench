#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int VCOS_UNSIGNED ;
struct TYPE_2__ {int size; char const* description; void* ptr; int /*<<< orphan*/  guardword; } ;
typedef  TYPE_1__ MALLOC_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  GUARDWORDHEAP ; 
 scalar_t__ VCOS_ALIGN_UP (char*,int) ; 
 void* _vcos_platform_malloc (int) ; 

void *vcos_generic_mem_alloc_aligned(VCOS_UNSIGNED size, VCOS_UNSIGNED align, const char *desc)
{
   int local_align = align == 0 ? 1 : align;
   int required_size = size + local_align + sizeof(MALLOC_HEADER_T);
   void *ptr = _vcos_platform_malloc(required_size);
   void *ret = NULL;
   MALLOC_HEADER_T *h;

   if (ptr)
   {
      ret = (void *)VCOS_ALIGN_UP(((char *)ptr)+sizeof(MALLOC_HEADER_T), local_align);
      h = ((MALLOC_HEADER_T *)ret)-1;
      h->size = size;
      h->description = desc;
      h->guardword = GUARDWORDHEAP;
      h->ptr = ptr;
   }

   return ret;
}