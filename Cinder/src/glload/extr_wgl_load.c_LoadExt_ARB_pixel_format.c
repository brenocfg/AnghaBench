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
typedef  scalar_t__ PFNWGLGETPIXELFORMATATTRIBIVARBPROC ;
typedef  scalar_t__ PFNWGLGETPIXELFORMATATTRIBFVARBPROC ;
typedef  scalar_t__ PFNWGLCHOOSEPIXELFORMATARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglChoosePixelFormatARB ; 
 scalar_t__ _funcptr_wglGetPixelFormatAttribfvARB ; 
 scalar_t__ _funcptr_wglGetPixelFormatAttribivARB ; 

__attribute__((used)) static int LoadExt_ARB_pixel_format()
{
	int numFailed = 0;
	_funcptr_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)IntGetProcAddress("wglChoosePixelFormatARB");
	if(!_funcptr_wglChoosePixelFormatARB) ++numFailed;
	_funcptr_wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)IntGetProcAddress("wglGetPixelFormatAttribfvARB");
	if(!_funcptr_wglGetPixelFormatAttribfvARB) ++numFailed;
	_funcptr_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)IntGetProcAddress("wglGetPixelFormatAttribivARB");
	if(!_funcptr_wglGetPixelFormatAttribivARB) ++numFailed;
	return numFailed;
}