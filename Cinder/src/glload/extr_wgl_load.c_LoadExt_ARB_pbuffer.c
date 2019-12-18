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
typedef  scalar_t__ PFNWGLRELEASEPBUFFERDCARBPROC ;
typedef  scalar_t__ PFNWGLQUERYPBUFFERARBPROC ;
typedef  scalar_t__ PFNWGLGETPBUFFERDCARBPROC ;
typedef  scalar_t__ PFNWGLDESTROYPBUFFERARBPROC ;
typedef  scalar_t__ PFNWGLCREATEPBUFFERARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglCreatePbufferARB ; 
 scalar_t__ _funcptr_wglDestroyPbufferARB ; 
 scalar_t__ _funcptr_wglGetPbufferDCARB ; 
 scalar_t__ _funcptr_wglQueryPbufferARB ; 
 scalar_t__ _funcptr_wglReleasePbufferDCARB ; 

__attribute__((used)) static int LoadExt_ARB_pbuffer()
{
	int numFailed = 0;
	_funcptr_wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)IntGetProcAddress("wglCreatePbufferARB");
	if(!_funcptr_wglCreatePbufferARB) ++numFailed;
	_funcptr_wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)IntGetProcAddress("wglDestroyPbufferARB");
	if(!_funcptr_wglDestroyPbufferARB) ++numFailed;
	_funcptr_wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)IntGetProcAddress("wglGetPbufferDCARB");
	if(!_funcptr_wglGetPbufferDCARB) ++numFailed;
	_funcptr_wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)IntGetProcAddress("wglQueryPbufferARB");
	if(!_funcptr_wglQueryPbufferARB) ++numFailed;
	_funcptr_wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)IntGetProcAddress("wglReleasePbufferDCARB");
	if(!_funcptr_wglReleasePbufferDCARB) ++numFailed;
	return numFailed;
}