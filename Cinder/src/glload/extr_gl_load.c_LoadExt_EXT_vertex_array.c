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
typedef  scalar_t__ PFNGLVERTEXPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVEXTPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSEXTPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLARRAYELEMENTEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glArrayElementEXT ; 
 scalar_t__ _funcptr_glColorPointerEXT ; 
 scalar_t__ _funcptr_glDrawArraysEXT ; 
 scalar_t__ _funcptr_glEdgeFlagPointerEXT ; 
 scalar_t__ _funcptr_glGetPointervEXT ; 
 scalar_t__ _funcptr_glIndexPointerEXT ; 
 scalar_t__ _funcptr_glNormalPointerEXT ; 
 scalar_t__ _funcptr_glTexCoordPointerEXT ; 
 scalar_t__ _funcptr_glVertexPointerEXT ; 

__attribute__((used)) static int LoadExt_EXT_vertex_array()
{
	int numFailed = 0;
	_funcptr_glArrayElementEXT = (PFNGLARRAYELEMENTEXTPROC)IntGetProcAddress("glArrayElementEXT");
	if(!_funcptr_glArrayElementEXT) ++numFailed;
	_funcptr_glColorPointerEXT = (PFNGLCOLORPOINTEREXTPROC)IntGetProcAddress("glColorPointerEXT");
	if(!_funcptr_glColorPointerEXT) ++numFailed;
	_funcptr_glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC)IntGetProcAddress("glDrawArraysEXT");
	if(!_funcptr_glDrawArraysEXT) ++numFailed;
	_funcptr_glEdgeFlagPointerEXT = (PFNGLEDGEFLAGPOINTEREXTPROC)IntGetProcAddress("glEdgeFlagPointerEXT");
	if(!_funcptr_glEdgeFlagPointerEXT) ++numFailed;
	_funcptr_glGetPointervEXT = (PFNGLGETPOINTERVEXTPROC)IntGetProcAddress("glGetPointervEXT");
	if(!_funcptr_glGetPointervEXT) ++numFailed;
	_funcptr_glIndexPointerEXT = (PFNGLINDEXPOINTEREXTPROC)IntGetProcAddress("glIndexPointerEXT");
	if(!_funcptr_glIndexPointerEXT) ++numFailed;
	_funcptr_glNormalPointerEXT = (PFNGLNORMALPOINTEREXTPROC)IntGetProcAddress("glNormalPointerEXT");
	if(!_funcptr_glNormalPointerEXT) ++numFailed;
	_funcptr_glTexCoordPointerEXT = (PFNGLTEXCOORDPOINTEREXTPROC)IntGetProcAddress("glTexCoordPointerEXT");
	if(!_funcptr_glTexCoordPointerEXT) ++numFailed;
	_funcptr_glVertexPointerEXT = (PFNGLVERTEXPOINTEREXTPROC)IntGetProcAddress("glVertexPointerEXT");
	if(!_funcptr_glVertexPointerEXT) ++numFailed;
	return numFailed;
}