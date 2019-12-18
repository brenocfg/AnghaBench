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
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 scalar_t__ EGL_SUCCESS ; 
 int /*<<< orphan*/  PS_destruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eglGetError () ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglReleaseThread () ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egldisplay ; 
 int /*<<< orphan*/  tiger ; 

void deinit(void)
{
	PS_destruct(tiger);
	eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	assert(eglGetError() == EGL_SUCCESS);
	eglTerminate(egldisplay);
	assert(eglGetError() == EGL_SUCCESS);
	eglReleaseThread();
}