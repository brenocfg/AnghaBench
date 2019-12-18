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
struct TYPE_2__ {int allocated; int /*<<< orphan*/ * surfaces; } ;
typedef  int /*<<< orphan*/  EGL_SURFACE_T ;

/* Variables and functions */
 int EGL_SURFACE_POOL_SIZE ; 
 scalar_t__ khrn_platform_malloc (int,char*) ; 
 TYPE_1__ surface_pool ; 

__attribute__((used)) static EGL_SURFACE_T* egl_surface_pool_alloc(void)
{
   int i = 0;

   while(surface_pool.allocated & (1 << i))
      i++;

   if (i < EGL_SURFACE_POOL_SIZE)
   {
      surface_pool.allocated |= 1 << i;
      return &surface_pool.surfaces[i];
   }
   else
   {
      return (EGL_SURFACE_T*)khrn_platform_malloc(sizeof(EGL_SURFACE_T), "EGL_SURFACE_T");
   }
}