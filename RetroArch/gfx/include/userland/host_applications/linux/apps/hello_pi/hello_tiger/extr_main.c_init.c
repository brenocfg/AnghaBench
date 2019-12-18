#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  NativeWindowType ;
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_ALPHA_SIZE 137 
#define  EGL_BLUE_SIZE 136 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
#define  EGL_DONT_CARE 135 
#define  EGL_GREEN_SIZE 134 
#define  EGL_LUMINANCE_SIZE 133 
#define  EGL_NONE 132 
 int /*<<< orphan*/  EGL_OPENVG_API ; 
#define  EGL_RED_SIZE 131 
#define  EGL_SAMPLES 130 
 scalar_t__ EGL_SUCCESS ; 
#define  EGL_SURFACE_TYPE 129 
#define  EGL_WINDOW_BIT 128 
 int /*<<< orphan*/  PS_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglChooseConfig (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglGetDisplay (int /*<<< orphan*/ ) ; 
 scalar_t__ eglGetError () ; 
 int /*<<< orphan*/  eglInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglconfig ; 
 int /*<<< orphan*/  eglcontext ; 
 int /*<<< orphan*/  egldisplay ; 
 int /*<<< orphan*/  eglsurface ; 
 int /*<<< orphan*/  tiger ; 
 int /*<<< orphan*/  tigerCommandCount ; 
 int /*<<< orphan*/  tigerCommands ; 
 int /*<<< orphan*/  tigerPointCount ; 
 int /*<<< orphan*/  tigerPoints ; 

void init(NativeWindowType window)
{
	static const EGLint s_configAttribs[] =
	{
		EGL_RED_SIZE,		8,
		EGL_GREEN_SIZE, 	8,
		EGL_BLUE_SIZE,		8,
		EGL_ALPHA_SIZE, 	8,
		EGL_LUMINANCE_SIZE, EGL_DONT_CARE,			//EGL_DONT_CARE
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_SAMPLES,		1,
		EGL_NONE
	};
	EGLint numconfigs;

	egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(egldisplay, NULL, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglBindAPI(EGL_OPENVG_API);

	eglChooseConfig(egldisplay, s_configAttribs, &eglconfig, 1, &numconfigs);
	assert(eglGetError() == EGL_SUCCESS);
	assert(numconfigs == 1);

	eglsurface = eglCreateWindowSurface(egldisplay, eglconfig, window, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglcontext = eglCreateContext(egldisplay, eglconfig, NULL, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglMakeCurrent(egldisplay, eglsurface, eglsurface, eglcontext);
	assert(eglGetError() == EGL_SUCCESS);

	tiger = PS_construct(tigerCommands, tigerCommandCount, tigerPoints, tigerPointCount);
}