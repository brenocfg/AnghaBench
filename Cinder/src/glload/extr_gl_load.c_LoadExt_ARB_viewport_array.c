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
typedef  scalar_t__ PFNGLVIEWPORTINDEXEDFVPROC ;
typedef  scalar_t__ PFNGLVIEWPORTINDEXEDFPROC ;
typedef  scalar_t__ PFNGLVIEWPORTARRAYVPROC ;
typedef  scalar_t__ PFNGLSCISSORINDEXEDVPROC ;
typedef  scalar_t__ PFNGLSCISSORINDEXEDPROC ;
typedef  scalar_t__ PFNGLSCISSORARRAYVPROC ;
typedef  scalar_t__ PFNGLGETFLOATI_VPROC ;
typedef  scalar_t__ PFNGLGETDOUBLEI_VPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEINDEXEDPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEARRAYVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDepthRangeArrayv ; 
 scalar_t__ _funcptr_glDepthRangeIndexed ; 
 scalar_t__ _funcptr_glGetDoublei_v ; 
 scalar_t__ _funcptr_glGetFloati_v ; 
 scalar_t__ _funcptr_glScissorArrayv ; 
 scalar_t__ _funcptr_glScissorIndexed ; 
 scalar_t__ _funcptr_glScissorIndexedv ; 
 scalar_t__ _funcptr_glViewportArrayv ; 
 scalar_t__ _funcptr_glViewportIndexedf ; 
 scalar_t__ _funcptr_glViewportIndexedfv ; 

__attribute__((used)) static int LoadExt_ARB_viewport_array()
{
	int numFailed = 0;
	_funcptr_glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)IntGetProcAddress("glDepthRangeArrayv");
	if(!_funcptr_glDepthRangeArrayv) ++numFailed;
	_funcptr_glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)IntGetProcAddress("glDepthRangeIndexed");
	if(!_funcptr_glDepthRangeIndexed) ++numFailed;
	_funcptr_glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)IntGetProcAddress("glGetDoublei_v");
	if(!_funcptr_glGetDoublei_v) ++numFailed;
	_funcptr_glGetFloati_v = (PFNGLGETFLOATI_VPROC)IntGetProcAddress("glGetFloati_v");
	if(!_funcptr_glGetFloati_v) ++numFailed;
	_funcptr_glScissorArrayv = (PFNGLSCISSORARRAYVPROC)IntGetProcAddress("glScissorArrayv");
	if(!_funcptr_glScissorArrayv) ++numFailed;
	_funcptr_glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)IntGetProcAddress("glScissorIndexed");
	if(!_funcptr_glScissorIndexed) ++numFailed;
	_funcptr_glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)IntGetProcAddress("glScissorIndexedv");
	if(!_funcptr_glScissorIndexedv) ++numFailed;
	_funcptr_glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)IntGetProcAddress("glViewportArrayv");
	if(!_funcptr_glViewportArrayv) ++numFailed;
	_funcptr_glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)IntGetProcAddress("glViewportIndexedf");
	if(!_funcptr_glViewportIndexedf) ++numFailed;
	_funcptr_glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)IntGetProcAddress("glViewportIndexedfv");
	if(!_funcptr_glViewportIndexedfv) ++numFailed;
	return numFailed;
}