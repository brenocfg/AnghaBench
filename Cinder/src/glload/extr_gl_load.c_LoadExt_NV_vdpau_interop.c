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
typedef  scalar_t__ PFNGLVDPAUUNREGISTERSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUUNMAPSURFACESNVPROC ;
typedef  scalar_t__ PFNGLVDPAUSURFACEACCESSNVPROC ;
typedef  scalar_t__ PFNGLVDPAUREGISTERVIDEOSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUMAPSURFACESNVPROC ;
typedef  scalar_t__ PFNGLVDPAUISSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUINITNVPROC ;
typedef  scalar_t__ PFNGLVDPAUGETSURFACEIVNVPROC ;
typedef  scalar_t__ PFNGLVDPAUFININVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glVDPAUFiniNV ; 
 scalar_t__ _funcptr_glVDPAUGetSurfaceivNV ; 
 scalar_t__ _funcptr_glVDPAUInitNV ; 
 scalar_t__ _funcptr_glVDPAUIsSurfaceNV ; 
 scalar_t__ _funcptr_glVDPAUMapSurfacesNV ; 
 scalar_t__ _funcptr_glVDPAURegisterOutputSurfaceNV ; 
 scalar_t__ _funcptr_glVDPAURegisterVideoSurfaceNV ; 
 scalar_t__ _funcptr_glVDPAUSurfaceAccessNV ; 
 scalar_t__ _funcptr_glVDPAUUnmapSurfacesNV ; 
 scalar_t__ _funcptr_glVDPAUUnregisterSurfaceNV ; 

__attribute__((used)) static int LoadExt_NV_vdpau_interop()
{
	int numFailed = 0;
	_funcptr_glVDPAUFiniNV = (PFNGLVDPAUFININVPROC)IntGetProcAddress("glVDPAUFiniNV");
	if(!_funcptr_glVDPAUFiniNV) ++numFailed;
	_funcptr_glVDPAUGetSurfaceivNV = (PFNGLVDPAUGETSURFACEIVNVPROC)IntGetProcAddress("glVDPAUGetSurfaceivNV");
	if(!_funcptr_glVDPAUGetSurfaceivNV) ++numFailed;
	_funcptr_glVDPAUInitNV = (PFNGLVDPAUINITNVPROC)IntGetProcAddress("glVDPAUInitNV");
	if(!_funcptr_glVDPAUInitNV) ++numFailed;
	_funcptr_glVDPAUIsSurfaceNV = (PFNGLVDPAUISSURFACENVPROC)IntGetProcAddress("glVDPAUIsSurfaceNV");
	if(!_funcptr_glVDPAUIsSurfaceNV) ++numFailed;
	_funcptr_glVDPAUMapSurfacesNV = (PFNGLVDPAUMAPSURFACESNVPROC)IntGetProcAddress("glVDPAUMapSurfacesNV");
	if(!_funcptr_glVDPAUMapSurfacesNV) ++numFailed;
	_funcptr_glVDPAURegisterOutputSurfaceNV = (PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)IntGetProcAddress("glVDPAURegisterOutputSurfaceNV");
	if(!_funcptr_glVDPAURegisterOutputSurfaceNV) ++numFailed;
	_funcptr_glVDPAURegisterVideoSurfaceNV = (PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)IntGetProcAddress("glVDPAURegisterVideoSurfaceNV");
	if(!_funcptr_glVDPAURegisterVideoSurfaceNV) ++numFailed;
	_funcptr_glVDPAUSurfaceAccessNV = (PFNGLVDPAUSURFACEACCESSNVPROC)IntGetProcAddress("glVDPAUSurfaceAccessNV");
	if(!_funcptr_glVDPAUSurfaceAccessNV) ++numFailed;
	_funcptr_glVDPAUUnmapSurfacesNV = (PFNGLVDPAUUNMAPSURFACESNVPROC)IntGetProcAddress("glVDPAUUnmapSurfacesNV");
	if(!_funcptr_glVDPAUUnmapSurfacesNV) ++numFailed;
	_funcptr_glVDPAUUnregisterSurfaceNV = (PFNGLVDPAUUNREGISTERSURFACENVPROC)IntGetProcAddress("glVDPAUUnregisterSurfaceNV");
	if(!_funcptr_glVDPAUUnregisterSurfaceNV) ++numFailed;
	return numFailed;
}