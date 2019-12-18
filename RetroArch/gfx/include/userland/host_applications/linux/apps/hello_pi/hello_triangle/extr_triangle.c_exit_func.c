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
struct TYPE_2__ {int /*<<< orphan*/  tex_buf3; int /*<<< orphan*/  tex_buf2; int /*<<< orphan*/  tex_buf1; int /*<<< orphan*/  display; int /*<<< orphan*/  context; int /*<<< orphan*/  dispman_display; int /*<<< orphan*/  dispman_element; int /*<<< orphan*/  surface; int /*<<< orphan*/  tex; } ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* state ; 
 int vc_dispmanx_display_close (int /*<<< orphan*/ ) ; 
 int vc_dispmanx_element_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exit_func(void)
// Function to be passed to atexit().
{
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   int s;
   // clear screen
   glClear( GL_COLOR_BUFFER_BIT );
   eglSwapBuffers(state->display, state->surface);

   glDeleteTextures(6, state->tex);
   eglDestroySurface( state->display, state->surface );

   dispman_update = vc_dispmanx_update_start( 0 );
   s = vc_dispmanx_element_remove(dispman_update, state->dispman_element);
   assert(s == 0);
   vc_dispmanx_update_submit_sync( dispman_update );
   s = vc_dispmanx_display_close(state->dispman_display);
   assert (s == 0);

   // Release OpenGL resources
   eglMakeCurrent( state->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
   eglDestroyContext( state->display, state->context );
   eglTerminate( state->display );

   // release texture buffers
   free(state->tex_buf1);
   free(state->tex_buf2);
   free(state->tex_buf3);

   printf("\ncube closed\n");
}