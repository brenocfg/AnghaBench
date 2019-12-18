#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int is_destroyed; scalar_t__ name; } ;
typedef  void KHRN_POINTER_MAP_T ;
typedef  TYPE_1__ EGL_SURFACE_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  UNUSED_NDEBUG (scalar_t__) ; 
 int /*<<< orphan*/  egl_surface_maybe_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static void callback_destroy_surface(KHRN_POINTER_MAP_T *map, uint32_t key, void *value, void *data)
{
   EGL_SURFACE_T *surface = (EGL_SURFACE_T *)value;

   UNUSED(map);
   UNUSED(data);
   UNUSED_NDEBUG(key);

   vcos_assert( surface != NULL );
   vcos_assert((uintptr_t)key == (uintptr_t)surface->name);

   surface->is_destroyed = true;
   egl_surface_maybe_free(surface);
}