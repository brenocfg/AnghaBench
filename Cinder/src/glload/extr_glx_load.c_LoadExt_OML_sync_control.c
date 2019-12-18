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
typedef  scalar_t__ PFNGLXWAITFORSBCOMLPROC ;
typedef  scalar_t__ PFNGLXWAITFORMSCOMLPROC ;
typedef  scalar_t__ PFNGLXSWAPBUFFERSMSCOMLPROC ;
typedef  scalar_t__ PFNGLXGETSYNCVALUESOMLPROC ;
typedef  scalar_t__ PFNGLXGETMSCRATEOMLPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXGetMscRateOML ; 
 scalar_t__ _funcptr_glXGetSyncValuesOML ; 
 scalar_t__ _funcptr_glXSwapBuffersMscOML ; 
 scalar_t__ _funcptr_glXWaitForMscOML ; 
 scalar_t__ _funcptr_glXWaitForSbcOML ; 

__attribute__((used)) static int LoadExt_OML_sync_control()
{
	int numFailed = 0;
	_funcptr_glXGetMscRateOML = (PFNGLXGETMSCRATEOMLPROC)IntGetProcAddress("glXGetMscRateOML");
	if(!_funcptr_glXGetMscRateOML) ++numFailed;
	_funcptr_glXGetSyncValuesOML = (PFNGLXGETSYNCVALUESOMLPROC)IntGetProcAddress("glXGetSyncValuesOML");
	if(!_funcptr_glXGetSyncValuesOML) ++numFailed;
	_funcptr_glXSwapBuffersMscOML = (PFNGLXSWAPBUFFERSMSCOMLPROC)IntGetProcAddress("glXSwapBuffersMscOML");
	if(!_funcptr_glXSwapBuffersMscOML) ++numFailed;
	_funcptr_glXWaitForMscOML = (PFNGLXWAITFORMSCOMLPROC)IntGetProcAddress("glXWaitForMscOML");
	if(!_funcptr_glXWaitForMscOML) ++numFailed;
	_funcptr_glXWaitForSbcOML = (PFNGLXWAITFORSBCOMLPROC)IntGetProcAddress("glXWaitForSbcOML");
	if(!_funcptr_glXWaitForSbcOML) ++numFailed;
	return numFailed;
}