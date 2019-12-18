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
typedef  scalar_t__ PFNGLVERTEXPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLFOGCOORDPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERLISTIBMPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glColorPointerListIBM ; 
 scalar_t__ _funcptr_glEdgeFlagPointerListIBM ; 
 scalar_t__ _funcptr_glFogCoordPointerListIBM ; 
 scalar_t__ _funcptr_glIndexPointerListIBM ; 
 scalar_t__ _funcptr_glNormalPointerListIBM ; 
 scalar_t__ _funcptr_glSecondaryColorPointerListIBM ; 
 scalar_t__ _funcptr_glTexCoordPointerListIBM ; 
 scalar_t__ _funcptr_glVertexPointerListIBM ; 

__attribute__((used)) static int LoadExt_IBM_vertex_array_lists()
{
	int numFailed = 0;
	_funcptr_glColorPointerListIBM = (PFNGLCOLORPOINTERLISTIBMPROC)IntGetProcAddress("glColorPointerListIBM");
	if(!_funcptr_glColorPointerListIBM) ++numFailed;
	_funcptr_glEdgeFlagPointerListIBM = (PFNGLEDGEFLAGPOINTERLISTIBMPROC)IntGetProcAddress("glEdgeFlagPointerListIBM");
	if(!_funcptr_glEdgeFlagPointerListIBM) ++numFailed;
	_funcptr_glFogCoordPointerListIBM = (PFNGLFOGCOORDPOINTERLISTIBMPROC)IntGetProcAddress("glFogCoordPointerListIBM");
	if(!_funcptr_glFogCoordPointerListIBM) ++numFailed;
	_funcptr_glIndexPointerListIBM = (PFNGLINDEXPOINTERLISTIBMPROC)IntGetProcAddress("glIndexPointerListIBM");
	if(!_funcptr_glIndexPointerListIBM) ++numFailed;
	_funcptr_glNormalPointerListIBM = (PFNGLNORMALPOINTERLISTIBMPROC)IntGetProcAddress("glNormalPointerListIBM");
	if(!_funcptr_glNormalPointerListIBM) ++numFailed;
	_funcptr_glSecondaryColorPointerListIBM = (PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)IntGetProcAddress("glSecondaryColorPointerListIBM");
	if(!_funcptr_glSecondaryColorPointerListIBM) ++numFailed;
	_funcptr_glTexCoordPointerListIBM = (PFNGLTEXCOORDPOINTERLISTIBMPROC)IntGetProcAddress("glTexCoordPointerListIBM");
	if(!_funcptr_glTexCoordPointerListIBM) ++numFailed;
	_funcptr_glVertexPointerListIBM = (PFNGLVERTEXPOINTERLISTIBMPROC)IntGetProcAddress("glVertexPointerListIBM");
	if(!_funcptr_glVertexPointerListIBM) ++numFailed;
	return numFailed;
}