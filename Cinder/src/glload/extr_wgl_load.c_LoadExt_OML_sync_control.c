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
typedef  scalar_t__ PFNWGLWAITFORSBCOMLPROC ;
typedef  scalar_t__ PFNWGLWAITFORMSCOMLPROC ;
typedef  scalar_t__ PFNWGLSWAPLAYERBUFFERSMSCOMLPROC ;
typedef  scalar_t__ PFNWGLSWAPBUFFERSMSCOMLPROC ;
typedef  scalar_t__ PFNWGLGETSYNCVALUESOMLPROC ;
typedef  scalar_t__ PFNWGLGETMSCRATEOMLPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglGetMscRateOML ; 
 scalar_t__ _funcptr_wglGetSyncValuesOML ; 
 scalar_t__ _funcptr_wglSwapBuffersMscOML ; 
 scalar_t__ _funcptr_wglSwapLayerBuffersMscOML ; 
 scalar_t__ _funcptr_wglWaitForMscOML ; 
 scalar_t__ _funcptr_wglWaitForSbcOML ; 

__attribute__((used)) static int LoadExt_OML_sync_control()
{
	int numFailed = 0;
	_funcptr_wglGetMscRateOML = (PFNWGLGETMSCRATEOMLPROC)IntGetProcAddress("wglGetMscRateOML");
	if(!_funcptr_wglGetMscRateOML) ++numFailed;
	_funcptr_wglGetSyncValuesOML = (PFNWGLGETSYNCVALUESOMLPROC)IntGetProcAddress("wglGetSyncValuesOML");
	if(!_funcptr_wglGetSyncValuesOML) ++numFailed;
	_funcptr_wglSwapBuffersMscOML = (PFNWGLSWAPBUFFERSMSCOMLPROC)IntGetProcAddress("wglSwapBuffersMscOML");
	if(!_funcptr_wglSwapBuffersMscOML) ++numFailed;
	_funcptr_wglSwapLayerBuffersMscOML = (PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)IntGetProcAddress("wglSwapLayerBuffersMscOML");
	if(!_funcptr_wglSwapLayerBuffersMscOML) ++numFailed;
	_funcptr_wglWaitForMscOML = (PFNWGLWAITFORMSCOMLPROC)IntGetProcAddress("wglWaitForMscOML");
	if(!_funcptr_wglWaitForMscOML) ++numFailed;
	_funcptr_wglWaitForSbcOML = (PFNWGLWAITFORSBCOMLPROC)IntGetProcAddress("wglWaitForSbcOML");
	if(!_funcptr_wglWaitForSbcOML) ++numFailed;
	return numFailed;
}