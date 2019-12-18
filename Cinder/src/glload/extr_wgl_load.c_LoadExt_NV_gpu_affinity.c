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
typedef  scalar_t__ PFNWGLENUMGPUSNVPROC ;
typedef  scalar_t__ PFNWGLENUMGPUSFROMAFFINITYDCNVPROC ;
typedef  scalar_t__ PFNWGLENUMGPUDEVICESNVPROC ;
typedef  scalar_t__ PFNWGLDELETEDCNVPROC ;
typedef  scalar_t__ PFNWGLCREATEAFFINITYDCNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglCreateAffinityDCNV ; 
 scalar_t__ _funcptr_wglDeleteDCNV ; 
 scalar_t__ _funcptr_wglEnumGpuDevicesNV ; 
 scalar_t__ _funcptr_wglEnumGpusFromAffinityDCNV ; 
 scalar_t__ _funcptr_wglEnumGpusNV ; 

__attribute__((used)) static int LoadExt_NV_gpu_affinity()
{
	int numFailed = 0;
	_funcptr_wglCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)IntGetProcAddress("wglCreateAffinityDCNV");
	if(!_funcptr_wglCreateAffinityDCNV) ++numFailed;
	_funcptr_wglDeleteDCNV = (PFNWGLDELETEDCNVPROC)IntGetProcAddress("wglDeleteDCNV");
	if(!_funcptr_wglDeleteDCNV) ++numFailed;
	_funcptr_wglEnumGpuDevicesNV = (PFNWGLENUMGPUDEVICESNVPROC)IntGetProcAddress("wglEnumGpuDevicesNV");
	if(!_funcptr_wglEnumGpuDevicesNV) ++numFailed;
	_funcptr_wglEnumGpusFromAffinityDCNV = (PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)IntGetProcAddress("wglEnumGpusFromAffinityDCNV");
	if(!_funcptr_wglEnumGpusFromAffinityDCNV) ++numFailed;
	_funcptr_wglEnumGpusNV = (PFNWGLENUMGPUSNVPROC)IntGetProcAddress("wglEnumGpusNV");
	if(!_funcptr_wglEnumGpusNV) ++numFailed;
	return numFailed;
}