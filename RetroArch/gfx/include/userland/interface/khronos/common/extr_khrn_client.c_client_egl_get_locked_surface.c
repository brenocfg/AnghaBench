#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  surfaces; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_destroyed; } ;
typedef  TYPE_1__ EGL_SURFACE_T ;
typedef  scalar_t__ EGLSurface ;
typedef  TYPE_2__ CLIENT_THREAD_STATE_T ;
typedef  TYPE_3__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_BAD_SURFACE ; 
 scalar_t__ khrn_pointer_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

EGL_SURFACE_T *client_egl_get_locked_surface(CLIENT_THREAD_STATE_T *thread, CLIENT_PROCESS_STATE_T *process, EGLSurface surf)
{
   EGL_SURFACE_T *surface = (EGL_SURFACE_T *)khrn_pointer_map_lookup(&process->surfaces, (uint32_t)(size_t)surf);

   vcos_assert (!surface || !surface->is_destroyed);

   if (!surface)
      thread->error = EGL_BAD_SURFACE;

   return surface;
}