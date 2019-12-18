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
struct TYPE_2__ {scalar_t__ guardword; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ MALLOC_HEADER_T ;

/* Variables and functions */
 scalar_t__ GUARDWORDHEAP ; 
 int /*<<< orphan*/  _vcos_platform_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void vcos_generic_mem_free(void *ptr)
{
   MALLOC_HEADER_T *h;
   if (! ptr) return;

   h = ((MALLOC_HEADER_T *)ptr)-1;
   vcos_assert(h->guardword == GUARDWORDHEAP);
   _vcos_platform_free(h->ptr);
}