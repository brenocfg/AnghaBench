#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int allocated; TYPE_1__* surfaces; } ;
struct TYPE_4__ {int avail_buffers_valid; int /*<<< orphan*/  avail_buffers; } ;
typedef  TYPE_1__ EGL_SURFACE_T ;

/* Variables and functions */
 unsigned int EGL_SURFACE_POOL_SIZE ; 
 int /*<<< orphan*/  khrn_platform_free (void*) ; 
 int /*<<< orphan*/  khronos_platform_semaphore_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__ surface_pool ; 

__attribute__((used)) static void egl_surface_pool_free(EGL_SURFACE_T* surface)
{
   unsigned int i = 0;

   /* todo: this doesn't belong here */
   //semaphore now gets destroyed on async callback from VC
   if (surface->avail_buffers_valid)
      khronos_platform_semaphore_destroy(&surface->avail_buffers);
   surface->avail_buffers_valid = false;

   i = (unsigned int) (surface - surface_pool.surfaces);

   if (i < EGL_SURFACE_POOL_SIZE)
   {
      surface_pool.allocated &= ~(1 << i);
   }
   else
   {
      khrn_platform_free((void*)surface);
   }
}