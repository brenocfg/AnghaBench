#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {int width; int height; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ VC_RECT_T ;
struct TYPE_10__ {scalar_t__ display; scalar_t__ context; int screen_width; int screen_height; int /*<<< orphan*/  surface; } ;
struct TYPE_9__ {int width; int height; int /*<<< orphan*/  element; } ;
typedef  int EGLint ;
typedef  TYPE_2__ EGL_DISPMANX_WINDOW_T ;
typedef  int /*<<< orphan*/  EGLConfig ;
typedef  scalar_t__ EGLBoolean ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;
typedef  int /*<<< orphan*/  DISPMANX_ELEMENT_HANDLE_T ;
typedef  int /*<<< orphan*/  DISPMANX_DISPLAY_HANDLE_T ;
typedef  TYPE_3__ CUBE_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  DISPMANX_PROTECTION_NONE ; 
#define  EGL_ALPHA_SIZE 136 
#define  EGL_BLUE_SIZE 135 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
#define  EGL_DEPTH_SIZE 134 
 scalar_t__ EGL_FALSE ; 
#define  EGL_GREEN_SIZE 133 
#define  EGL_NONE 132 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
#define  EGL_RED_SIZE 131 
#define  EGL_SAMPLES 130 
#define  EGL_SURFACE_TYPE 129 
#define  EGL_WINDOW_BIT 128 
 int /*<<< orphan*/  GL_AMBIENT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eglCreateContext (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 scalar_t__ eglInitialize (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eglMakeCurrent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eglSaneChooseConfigBRCM (scalar_t__,int const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepthf (double) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLightfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ graphics_get_display_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  vc_dispmanx_display_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_element_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_ogl(CUBE_STATE_T *state)
{
   int32_t success = 0;
   EGLBoolean result;
   EGLint num_config;

   static EGL_DISPMANX_WINDOW_T nativewindow;

   DISPMANX_ELEMENT_HANDLE_T dispman_element;
   DISPMANX_DISPLAY_HANDLE_T dispman_display;
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   VC_RECT_T dst_rect;
   VC_RECT_T src_rect;

   static const EGLint attribute_list[] =
   {
      EGL_RED_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_DEPTH_SIZE, 16,
      EGL_SAMPLES, 4,
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_NONE
   };

   EGLConfig config;

   // get an EGL display connection
   state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   assert(state->display!=EGL_NO_DISPLAY);

   // initialize the EGL display connection
   result = eglInitialize(state->display, NULL, NULL);
   assert(EGL_FALSE != result);

   // get an appropriate EGL frame buffer configuration
   // this uses a BRCM extension that gets the closest match, rather than standard which returns anything that matches
   result = eglSaneChooseConfigBRCM(state->display, attribute_list, &config, 1, &num_config);
   assert(EGL_FALSE != result);

   // create an EGL rendering context
   state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, NULL);
   assert(state->context!=EGL_NO_CONTEXT);

   // create an EGL window surface
   success = graphics_get_display_size(0 /* LCD */, &state->screen_width, &state->screen_height);
   assert( success >= 0 );

   dst_rect.x = 0;
   dst_rect.y = 0;
   dst_rect.width = state->screen_width;
   dst_rect.height = state->screen_height;

   src_rect.x = 0;
   src_rect.y = 0;
   src_rect.width = state->screen_width << 16;
   src_rect.height = state->screen_height << 16;

   dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   dispman_update = vc_dispmanx_update_start( 0 );

   dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
      0/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);

   nativewindow.element = dispman_element;
   nativewindow.width = state->screen_width;
   nativewindow.height = state->screen_height;
   vc_dispmanx_update_submit_sync( dispman_update );

   state->surface = eglCreateWindowSurface( state->display, config, &nativewindow, NULL );
   assert(state->surface != EGL_NO_SURFACE);

   // connect the context to the surface
   result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
   assert(EGL_FALSE != result);

   // Set background color and clear buffers
   glClearColor((0.3922f+7*0.5f)/8, (0.1176f+7*0.5f)/8, (0.5882f+7*0.5f)/8, 1.0f);

   // Enable back face culling.
   glEnable(GL_CULL_FACE);

   glEnable(GL_DEPTH_TEST);
   glClearDepthf(1.0);
   glDepthFunc(GL_LEQUAL);

   float noAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
   glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHTING);
}