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
typedef  scalar_t__ PFNGLTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLPOLYGONOFFSETPROC ;
typedef  scalar_t__ PFNGLISTEXTUREPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVPROC ;
typedef  scalar_t__ PFNGLGENTEXTURESPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSPROC ;
typedef  scalar_t__ PFNGLDELETETEXTURESPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLBINDTEXTUREPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindTexture ; 
 scalar_t__ _funcptr_glCopyTexImage1D ; 
 scalar_t__ _funcptr_glCopyTexImage2D ; 
 scalar_t__ _funcptr_glCopyTexSubImage1D ; 
 scalar_t__ _funcptr_glCopyTexSubImage2D ; 
 scalar_t__ _funcptr_glDeleteTextures ; 
 scalar_t__ _funcptr_glDrawArrays ; 
 scalar_t__ _funcptr_glDrawElements ; 
 scalar_t__ _funcptr_glGenTextures ; 
 scalar_t__ _funcptr_glGetPointerv ; 
 scalar_t__ _funcptr_glIsTexture ; 
 scalar_t__ _funcptr_glPolygonOffset ; 
 scalar_t__ _funcptr_glTexSubImage1D ; 
 scalar_t__ _funcptr_glTexSubImage2D ; 

__attribute__((used)) static int LoadCore_Version_1_1()
{
	int numFailed = 0;
	_funcptr_glBindTexture = (PFNGLBINDTEXTUREPROC)IntGetProcAddress("glBindTexture");
	if(!_funcptr_glBindTexture) ++numFailed;
	_funcptr_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)IntGetProcAddress("glCopyTexImage1D");
	if(!_funcptr_glCopyTexImage1D) ++numFailed;
	_funcptr_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)IntGetProcAddress("glCopyTexImage2D");
	if(!_funcptr_glCopyTexImage2D) ++numFailed;
	_funcptr_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)IntGetProcAddress("glCopyTexSubImage1D");
	if(!_funcptr_glCopyTexSubImage1D) ++numFailed;
	_funcptr_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)IntGetProcAddress("glCopyTexSubImage2D");
	if(!_funcptr_glCopyTexSubImage2D) ++numFailed;
	_funcptr_glDeleteTextures = (PFNGLDELETETEXTURESPROC)IntGetProcAddress("glDeleteTextures");
	if(!_funcptr_glDeleteTextures) ++numFailed;
	_funcptr_glDrawArrays = (PFNGLDRAWARRAYSPROC)IntGetProcAddress("glDrawArrays");
	if(!_funcptr_glDrawArrays) ++numFailed;
	_funcptr_glDrawElements = (PFNGLDRAWELEMENTSPROC)IntGetProcAddress("glDrawElements");
	if(!_funcptr_glDrawElements) ++numFailed;
	_funcptr_glGenTextures = (PFNGLGENTEXTURESPROC)IntGetProcAddress("glGenTextures");
	if(!_funcptr_glGenTextures) ++numFailed;
	_funcptr_glGetPointerv = (PFNGLGETPOINTERVPROC)IntGetProcAddress("glGetPointerv");
	if(!_funcptr_glGetPointerv) ++numFailed;
	_funcptr_glIsTexture = (PFNGLISTEXTUREPROC)IntGetProcAddress("glIsTexture");
	if(!_funcptr_glIsTexture) ++numFailed;
	_funcptr_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)IntGetProcAddress("glPolygonOffset");
	if(!_funcptr_glPolygonOffset) ++numFailed;
	_funcptr_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)IntGetProcAddress("glTexSubImage1D");
	if(!_funcptr_glTexSubImage1D) ++numFailed;
	_funcptr_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)IntGetProcAddress("glTexSubImage2D");
	if(!_funcptr_glTexSubImage2D) ++numFailed;
	return numFailed;
}