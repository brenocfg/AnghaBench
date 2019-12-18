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

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  ectxt ; 
 scalar_t__ edpy ; 
 int /*<<< orphan*/  eglDestroyContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 
 scalar_t__ esfc ; 
 void* gl_es_display ; 
 void* gl_es_surface ; 
 int /*<<< orphan*/  gl_platform_finish () ; 

void gl_finish(void)
{
	eglMakeCurrent(edpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(edpy, ectxt);
	ectxt = EGL_NO_CONTEXT;
	eglDestroySurface(edpy, esfc);
	esfc = EGL_NO_SURFACE;
	eglTerminate(edpy);
	edpy = EGL_NO_DISPLAY;

	gl_es_display = (void *)edpy;
	gl_es_surface = (void *)esfc;

	gl_platform_finish();
}