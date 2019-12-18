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
 scalar_t__ EGL_SUCCESS ; 
 int /*<<< orphan*/  PS_render (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VG_CLEAR_COLOR ; 
 scalar_t__ VG_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eglGetError () ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egldisplay ; 
 int /*<<< orphan*/  eglsurface ; 
 int renderHeight ; 
 int renderWidth ; 
 int /*<<< orphan*/  rotateN ; 
 int /*<<< orphan*/  tiger ; 
 int tigerMaxX ; 
 int tigerMaxY ; 
 int tigerMinX ; 
 int tigerMinY ; 
 int /*<<< orphan*/  vgClear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ vgGetError () ; 
 int /*<<< orphan*/  vgLoadIdentity () ; 
 int /*<<< orphan*/  vgRotate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgScale (float,float) ; 
 int /*<<< orphan*/  vgSetfv (int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  vgTranslate (int,int) ; 

void render(int w, int h)
{
#ifndef __RASPBERRYPI__
	if(renderWidth != w || renderHeight != h)
#endif
	{
		float clearColor[4] = {1,1,1,1};
		float scale = w / (tigerMaxX - tigerMinX);

		eglSwapBuffers(egldisplay, eglsurface);	//force EGL to recognize resize

		vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
		vgClear(0, 0, w, h);

		vgLoadIdentity();
#ifdef __RASPBERRYPI__
                vgTranslate(w * 0.5f, h * 0.5f);
                vgRotate(rotateN);
                vgTranslate(-w * 0.5f, -h * 0.5f);
#endif
		vgScale(scale, scale);
		vgTranslate(-tigerMinX, -tigerMinY + 0.5f * (h / scale - (tigerMaxY - tigerMinY)));

		PS_render(tiger);
		assert(vgGetError() == VG_NO_ERROR);

		renderWidth = w;
		renderHeight = h;
	}
#ifndef __RASPBERRYPI__
	eglSwapBuffers(egldisplay, eglsurface);
	assert(eglGetError() == EGL_SUCCESS);
#endif
}