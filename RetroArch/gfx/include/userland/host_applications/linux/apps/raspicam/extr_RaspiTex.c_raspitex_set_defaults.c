#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  close; int /*<<< orphan*/  destroy_native_window; int /*<<< orphan*/  gl_term; int /*<<< orphan*/  capture; int /*<<< orphan*/  redraw; int /*<<< orphan*/  update_model; int /*<<< orphan*/  gl_init; int /*<<< orphan*/  create_native_window; } ;
struct TYPE_6__ {int opacity; TYPE_1__ ops; int /*<<< orphan*/  scene_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; void* v_egl_image; void* u_egl_image; void* y_egl_image; void* egl_image; int /*<<< orphan*/  context; int /*<<< orphan*/  surface; int /*<<< orphan*/  display; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; } ;
typedef  TYPE_2__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_HEIGHT ; 
 int /*<<< orphan*/  DEFAULT_WIDTH ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_DISPLAY ; 
 void* EGL_NO_IMAGE_KHR ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  RASPITEX_SCENE_SQUARE ; 
 int /*<<< orphan*/  RASPITEX_VERSION_MAJOR ; 
 int /*<<< orphan*/  RASPITEX_VERSION_MINOR ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raspitexutil_capture_bgra ; 
 int /*<<< orphan*/  raspitexutil_close ; 
 int /*<<< orphan*/  raspitexutil_create_native_window ; 
 int /*<<< orphan*/  raspitexutil_destroy_native_window ; 
 int /*<<< orphan*/  raspitexutil_gl_init_1_0 ; 
 int /*<<< orphan*/  raspitexutil_gl_term ; 
 int /*<<< orphan*/  raspitexutil_redraw ; 
 int /*<<< orphan*/  raspitexutil_update_model ; 

void raspitex_set_defaults(RASPITEX_STATE *state)
{
   memset(state, 0, sizeof(*state));
   state->version_major = RASPITEX_VERSION_MAJOR;
   state->version_minor = RASPITEX_VERSION_MINOR;
   state->display = EGL_NO_DISPLAY;
   state->surface = EGL_NO_SURFACE;
   state->context = EGL_NO_CONTEXT;
   state->egl_image = EGL_NO_IMAGE_KHR;
   state->y_egl_image = EGL_NO_IMAGE_KHR;
   state->u_egl_image = EGL_NO_IMAGE_KHR;
   state->v_egl_image = EGL_NO_IMAGE_KHR;
   state->opacity = 255;
   state->width = DEFAULT_WIDTH;
   state->height = DEFAULT_HEIGHT;
   state->scene_id = RASPITEX_SCENE_SQUARE;

   state->ops.create_native_window = raspitexutil_create_native_window;
   state->ops.gl_init = raspitexutil_gl_init_1_0;
   state->ops.update_model = raspitexutil_update_model;
   state->ops.redraw = raspitexutil_redraw;
   state->ops.capture = raspitexutil_capture_bgra;
   state->ops.gl_term = raspitexutil_gl_term;
   state->ops.destroy_native_window = raspitexutil_destroy_native_window;
   state->ops.close = raspitexutil_close;
}