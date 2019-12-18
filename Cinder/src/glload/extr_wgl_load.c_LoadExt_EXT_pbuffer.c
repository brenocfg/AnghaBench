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
typedef  scalar_t__ PFNWGLRELEASEPBUFFERDCEXTPROC ;
typedef  scalar_t__ PFNWGLQUERYPBUFFEREXTPROC ;
typedef  scalar_t__ PFNWGLGETPBUFFERDCEXTPROC ;
typedef  scalar_t__ PFNWGLDESTROYPBUFFEREXTPROC ;
typedef  scalar_t__ PFNWGLCREATEPBUFFEREXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglCreatePbufferEXT ; 
 scalar_t__ _funcptr_wglDestroyPbufferEXT ; 
 scalar_t__ _funcptr_wglGetPbufferDCEXT ; 
 scalar_t__ _funcptr_wglQueryPbufferEXT ; 
 scalar_t__ _funcptr_wglReleasePbufferDCEXT ; 

__attribute__((used)) static int LoadExt_EXT_pbuffer()
{
	int numFailed = 0;
	_funcptr_wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)IntGetProcAddress("wglCreatePbufferEXT");
	if(!_funcptr_wglCreatePbufferEXT) ++numFailed;
	_funcptr_wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)IntGetProcAddress("wglDestroyPbufferEXT");
	if(!_funcptr_wglDestroyPbufferEXT) ++numFailed;
	_funcptr_wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)IntGetProcAddress("wglGetPbufferDCEXT");
	if(!_funcptr_wglGetPbufferDCEXT) ++numFailed;
	_funcptr_wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)IntGetProcAddress("wglQueryPbufferEXT");
	if(!_funcptr_wglQueryPbufferEXT) ++numFailed;
	_funcptr_wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)IntGetProcAddress("wglReleasePbufferDCEXT");
	if(!_funcptr_wglReleasePbufferDCEXT) ++numFailed;
	return numFailed;
}