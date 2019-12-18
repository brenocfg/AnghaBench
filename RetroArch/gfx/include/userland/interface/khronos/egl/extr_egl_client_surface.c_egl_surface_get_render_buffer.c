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
struct TYPE_3__ {int type; int buffers; } ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  TYPE_1__ EGL_SURFACE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_BACK_BUFFER ; 
 int /*<<< orphan*/  EGL_NONE ; 
 int /*<<< orphan*/  EGL_SINGLE_BUFFER ; 
#define  PBUFFER 130 
#define  PIXMAP 129 
 int /*<<< orphan*/  UNREACHABLE () ; 
#define  WINDOW 128 

EGLint egl_surface_get_render_buffer(EGL_SURFACE_T *surface)
{
   switch (surface->type) {
   case WINDOW:
      if (surface->buffers == 1)
         return EGL_SINGLE_BUFFER;
      else
         return EGL_BACK_BUFFER;
   case PBUFFER:
      return EGL_BACK_BUFFER;
   case PIXMAP:
      return EGL_SINGLE_BUFFER;
   default:
      UNREACHABLE();
      return EGL_NONE;
   }
}