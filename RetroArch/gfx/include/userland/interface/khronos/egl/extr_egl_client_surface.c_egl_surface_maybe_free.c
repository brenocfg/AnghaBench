#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ context_binding_count; int /*<<< orphan*/  is_destroyed; } ;
typedef  TYPE_1__ EGL_SURFACE_T ;

/* Variables and functions */
 int /*<<< orphan*/  egl_surface_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 

void egl_surface_maybe_free(EGL_SURFACE_T *surface)
{
   vcos_assert(surface);

   if (!surface->is_destroyed)
      return;

   if (surface->context_binding_count)
      return;

   egl_surface_free(surface);
}