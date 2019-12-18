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
typedef  scalar_t__ PFNGLREADNPIXELSARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMFVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMDVARBPROC ;
typedef  scalar_t__ PFNGLGETNTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNSEPARABLEFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNPOLYGONSTIPPLEARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUSVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMINMAXARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPIVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPDVARBPROC ;
typedef  scalar_t__ PFNGLGETNHISTOGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETNCONVOLUTIONFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNCOLORTABLEARBPROC ;
typedef  scalar_t__ PFNGLGETGRAPHICSRESETSTATUSARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetGraphicsResetStatusARB ; 
 scalar_t__ _funcptr_glGetnColorTableARB ; 
 scalar_t__ _funcptr_glGetnCompressedTexImageARB ; 
 scalar_t__ _funcptr_glGetnConvolutionFilterARB ; 
 scalar_t__ _funcptr_glGetnHistogramARB ; 
 scalar_t__ _funcptr_glGetnMapdvARB ; 
 scalar_t__ _funcptr_glGetnMapfvARB ; 
 scalar_t__ _funcptr_glGetnMapivARB ; 
 scalar_t__ _funcptr_glGetnMinmaxARB ; 
 scalar_t__ _funcptr_glGetnPixelMapfvARB ; 
 scalar_t__ _funcptr_glGetnPixelMapuivARB ; 
 scalar_t__ _funcptr_glGetnPixelMapusvARB ; 
 scalar_t__ _funcptr_glGetnPolygonStippleARB ; 
 scalar_t__ _funcptr_glGetnSeparableFilterARB ; 
 scalar_t__ _funcptr_glGetnTexImageARB ; 
 scalar_t__ _funcptr_glGetnUniformdvARB ; 
 scalar_t__ _funcptr_glGetnUniformfvARB ; 
 scalar_t__ _funcptr_glGetnUniformivARB ; 
 scalar_t__ _funcptr_glGetnUniformuivARB ; 
 scalar_t__ _funcptr_glReadnPixelsARB ; 

__attribute__((used)) static int LoadExt_ARB_robustness()
{
	int numFailed = 0;
	_funcptr_glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC)IntGetProcAddress("glGetGraphicsResetStatusARB");
	if(!_funcptr_glGetGraphicsResetStatusARB) ++numFailed;
	_funcptr_glGetnColorTableARB = (PFNGLGETNCOLORTABLEARBPROC)IntGetProcAddress("glGetnColorTableARB");
	if(!_funcptr_glGetnColorTableARB) ++numFailed;
	_funcptr_glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)IntGetProcAddress("glGetnCompressedTexImageARB");
	if(!_funcptr_glGetnCompressedTexImageARB) ++numFailed;
	_funcptr_glGetnConvolutionFilterARB = (PFNGLGETNCONVOLUTIONFILTERARBPROC)IntGetProcAddress("glGetnConvolutionFilterARB");
	if(!_funcptr_glGetnConvolutionFilterARB) ++numFailed;
	_funcptr_glGetnHistogramARB = (PFNGLGETNHISTOGRAMARBPROC)IntGetProcAddress("glGetnHistogramARB");
	if(!_funcptr_glGetnHistogramARB) ++numFailed;
	_funcptr_glGetnMapdvARB = (PFNGLGETNMAPDVARBPROC)IntGetProcAddress("glGetnMapdvARB");
	if(!_funcptr_glGetnMapdvARB) ++numFailed;
	_funcptr_glGetnMapfvARB = (PFNGLGETNMAPFVARBPROC)IntGetProcAddress("glGetnMapfvARB");
	if(!_funcptr_glGetnMapfvARB) ++numFailed;
	_funcptr_glGetnMapivARB = (PFNGLGETNMAPIVARBPROC)IntGetProcAddress("glGetnMapivARB");
	if(!_funcptr_glGetnMapivARB) ++numFailed;
	_funcptr_glGetnMinmaxARB = (PFNGLGETNMINMAXARBPROC)IntGetProcAddress("glGetnMinmaxARB");
	if(!_funcptr_glGetnMinmaxARB) ++numFailed;
	_funcptr_glGetnPixelMapfvARB = (PFNGLGETNPIXELMAPFVARBPROC)IntGetProcAddress("glGetnPixelMapfvARB");
	if(!_funcptr_glGetnPixelMapfvARB) ++numFailed;
	_funcptr_glGetnPixelMapuivARB = (PFNGLGETNPIXELMAPUIVARBPROC)IntGetProcAddress("glGetnPixelMapuivARB");
	if(!_funcptr_glGetnPixelMapuivARB) ++numFailed;
	_funcptr_glGetnPixelMapusvARB = (PFNGLGETNPIXELMAPUSVARBPROC)IntGetProcAddress("glGetnPixelMapusvARB");
	if(!_funcptr_glGetnPixelMapusvARB) ++numFailed;
	_funcptr_glGetnPolygonStippleARB = (PFNGLGETNPOLYGONSTIPPLEARBPROC)IntGetProcAddress("glGetnPolygonStippleARB");
	if(!_funcptr_glGetnPolygonStippleARB) ++numFailed;
	_funcptr_glGetnSeparableFilterARB = (PFNGLGETNSEPARABLEFILTERARBPROC)IntGetProcAddress("glGetnSeparableFilterARB");
	if(!_funcptr_glGetnSeparableFilterARB) ++numFailed;
	_funcptr_glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC)IntGetProcAddress("glGetnTexImageARB");
	if(!_funcptr_glGetnTexImageARB) ++numFailed;
	_funcptr_glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC)IntGetProcAddress("glGetnUniformdvARB");
	if(!_funcptr_glGetnUniformdvARB) ++numFailed;
	_funcptr_glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC)IntGetProcAddress("glGetnUniformfvARB");
	if(!_funcptr_glGetnUniformfvARB) ++numFailed;
	_funcptr_glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC)IntGetProcAddress("glGetnUniformivARB");
	if(!_funcptr_glGetnUniformivARB) ++numFailed;
	_funcptr_glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC)IntGetProcAddress("glGetnUniformuivARB");
	if(!_funcptr_glGetnUniformuivARB) ++numFailed;
	_funcptr_glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC)IntGetProcAddress("glReadnPixelsARB");
	if(!_funcptr_glReadnPixelsARB) ++numFailed;
	return numFailed;
}