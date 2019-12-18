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
typedef  scalar_t__ PFNGLPOINTPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERIPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSPROC ;
typedef  scalar_t__ PFNGLBLENDFUNCSEPARATEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBlendFuncSeparate ; 
 scalar_t__ _funcptr_glMultiDrawArrays ; 
 scalar_t__ _funcptr_glMultiDrawElements ; 
 scalar_t__ _funcptr_glPointParameterf ; 
 scalar_t__ _funcptr_glPointParameterfv ; 
 scalar_t__ _funcptr_glPointParameteri ; 
 scalar_t__ _funcptr_glPointParameteriv ; 

__attribute__((used)) static int LoadCore_Version_1_4()
{
	int numFailed = 0;
	_funcptr_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)IntGetProcAddress("glBlendFuncSeparate");
	if(!_funcptr_glBlendFuncSeparate) ++numFailed;
	_funcptr_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)IntGetProcAddress("glMultiDrawArrays");
	if(!_funcptr_glMultiDrawArrays) ++numFailed;
	_funcptr_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)IntGetProcAddress("glMultiDrawElements");
	if(!_funcptr_glMultiDrawElements) ++numFailed;
	_funcptr_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)IntGetProcAddress("glPointParameterf");
	if(!_funcptr_glPointParameterf) ++numFailed;
	_funcptr_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)IntGetProcAddress("glPointParameterfv");
	if(!_funcptr_glPointParameterfv) ++numFailed;
	_funcptr_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)IntGetProcAddress("glPointParameteri");
	if(!_funcptr_glPointParameteri) ++numFailed;
	_funcptr_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)IntGetProcAddress("glPointParameteriv");
	if(!_funcptr_glPointParameteriv) ++numFailed;
	return numFailed;
}