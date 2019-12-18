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
typedef  scalar_t__ PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC ;
typedef  scalar_t__ PFNWGLGETGPUINFOAMDPROC ;
typedef  scalar_t__ PFNWGLGETGPUIDSAMDPROC ;
typedef  scalar_t__ PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC ;
typedef  scalar_t__ PFNWGLGETCONTEXTGPUIDAMDPROC ;
typedef  scalar_t__ PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC ;
typedef  scalar_t__ PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC ;
typedef  scalar_t__ PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC ;
typedef  scalar_t__ PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglBlitContextFramebufferAMD ; 
 scalar_t__ _funcptr_wglCreateAssociatedContextAMD ; 
 scalar_t__ _funcptr_wglCreateAssociatedContextAttribsAMD ; 
 scalar_t__ _funcptr_wglDeleteAssociatedContextAMD ; 
 scalar_t__ _funcptr_wglGetContextGPUIDAMD ; 
 scalar_t__ _funcptr_wglGetCurrentAssociatedContextAMD ; 
 scalar_t__ _funcptr_wglGetGPUIDsAMD ; 
 scalar_t__ _funcptr_wglGetGPUInfoAMD ; 
 scalar_t__ _funcptr_wglMakeAssociatedContextCurrentAMD ; 

__attribute__((used)) static int LoadExt_AMD_gpu_association()
{
	int numFailed = 0;
	_funcptr_wglBlitContextFramebufferAMD = (PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)IntGetProcAddress("wglBlitContextFramebufferAMD");
	if(!_funcptr_wglBlitContextFramebufferAMD) ++numFailed;
	_funcptr_wglCreateAssociatedContextAMD = (PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)IntGetProcAddress("wglCreateAssociatedContextAMD");
	if(!_funcptr_wglCreateAssociatedContextAMD) ++numFailed;
	_funcptr_wglCreateAssociatedContextAttribsAMD = (PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)IntGetProcAddress("wglCreateAssociatedContextAttribsAMD");
	if(!_funcptr_wglCreateAssociatedContextAttribsAMD) ++numFailed;
	_funcptr_wglDeleteAssociatedContextAMD = (PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)IntGetProcAddress("wglDeleteAssociatedContextAMD");
	if(!_funcptr_wglDeleteAssociatedContextAMD) ++numFailed;
	_funcptr_wglGetContextGPUIDAMD = (PFNWGLGETCONTEXTGPUIDAMDPROC)IntGetProcAddress("wglGetContextGPUIDAMD");
	if(!_funcptr_wglGetContextGPUIDAMD) ++numFailed;
	_funcptr_wglGetCurrentAssociatedContextAMD = (PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)IntGetProcAddress("wglGetCurrentAssociatedContextAMD");
	if(!_funcptr_wglGetCurrentAssociatedContextAMD) ++numFailed;
	_funcptr_wglGetGPUIDsAMD = (PFNWGLGETGPUIDSAMDPROC)IntGetProcAddress("wglGetGPUIDsAMD");
	if(!_funcptr_wglGetGPUIDsAMD) ++numFailed;
	_funcptr_wglGetGPUInfoAMD = (PFNWGLGETGPUINFOAMDPROC)IntGetProcAddress("wglGetGPUInfoAMD");
	if(!_funcptr_wglGetGPUInfoAMD) ++numFailed;
	_funcptr_wglMakeAssociatedContextCurrentAMD = (PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)IntGetProcAddress("wglMakeAssociatedContextCurrentAMD");
	if(!_funcptr_wglMakeAssociatedContextCurrentAMD) ++numFailed;
	return numFailed;
}