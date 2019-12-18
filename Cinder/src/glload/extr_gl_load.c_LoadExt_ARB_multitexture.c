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
typedef  scalar_t__ PFNGLMULTITEXCOORD4SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DARBPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVETEXTUREARBPROC ;
typedef  scalar_t__ PFNGLACTIVETEXTUREARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glActiveTextureARB ; 
 scalar_t__ _funcptr_glClientActiveTextureARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1dARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1dvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1fARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1fvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1iARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1ivARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1sARB ; 
 scalar_t__ _funcptr_glMultiTexCoord1svARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2dARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2dvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2fARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2fvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2iARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2ivARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2sARB ; 
 scalar_t__ _funcptr_glMultiTexCoord2svARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3dARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3dvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3fARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3fvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3iARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3ivARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3sARB ; 
 scalar_t__ _funcptr_glMultiTexCoord3svARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4dARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4dvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4fARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4fvARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4iARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4ivARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4sARB ; 
 scalar_t__ _funcptr_glMultiTexCoord4svARB ; 

__attribute__((used)) static int LoadExt_ARB_multitexture()
{
	int numFailed = 0;
	_funcptr_glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)IntGetProcAddress("glActiveTextureARB");
	if(!_funcptr_glActiveTextureARB) ++numFailed;
	_funcptr_glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)IntGetProcAddress("glClientActiveTextureARB");
	if(!_funcptr_glClientActiveTextureARB) ++numFailed;
	_funcptr_glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)IntGetProcAddress("glMultiTexCoord1dARB");
	if(!_funcptr_glMultiTexCoord1dARB) ++numFailed;
	_funcptr_glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)IntGetProcAddress("glMultiTexCoord1dvARB");
	if(!_funcptr_glMultiTexCoord1dvARB) ++numFailed;
	_funcptr_glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)IntGetProcAddress("glMultiTexCoord1fARB");
	if(!_funcptr_glMultiTexCoord1fARB) ++numFailed;
	_funcptr_glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)IntGetProcAddress("glMultiTexCoord1fvARB");
	if(!_funcptr_glMultiTexCoord1fvARB) ++numFailed;
	_funcptr_glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)IntGetProcAddress("glMultiTexCoord1iARB");
	if(!_funcptr_glMultiTexCoord1iARB) ++numFailed;
	_funcptr_glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)IntGetProcAddress("glMultiTexCoord1ivARB");
	if(!_funcptr_glMultiTexCoord1ivARB) ++numFailed;
	_funcptr_glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)IntGetProcAddress("glMultiTexCoord1sARB");
	if(!_funcptr_glMultiTexCoord1sARB) ++numFailed;
	_funcptr_glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)IntGetProcAddress("glMultiTexCoord1svARB");
	if(!_funcptr_glMultiTexCoord1svARB) ++numFailed;
	_funcptr_glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)IntGetProcAddress("glMultiTexCoord2dARB");
	if(!_funcptr_glMultiTexCoord2dARB) ++numFailed;
	_funcptr_glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)IntGetProcAddress("glMultiTexCoord2dvARB");
	if(!_funcptr_glMultiTexCoord2dvARB) ++numFailed;
	_funcptr_glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)IntGetProcAddress("glMultiTexCoord2fARB");
	if(!_funcptr_glMultiTexCoord2fARB) ++numFailed;
	_funcptr_glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)IntGetProcAddress("glMultiTexCoord2fvARB");
	if(!_funcptr_glMultiTexCoord2fvARB) ++numFailed;
	_funcptr_glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)IntGetProcAddress("glMultiTexCoord2iARB");
	if(!_funcptr_glMultiTexCoord2iARB) ++numFailed;
	_funcptr_glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)IntGetProcAddress("glMultiTexCoord2ivARB");
	if(!_funcptr_glMultiTexCoord2ivARB) ++numFailed;
	_funcptr_glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)IntGetProcAddress("glMultiTexCoord2sARB");
	if(!_funcptr_glMultiTexCoord2sARB) ++numFailed;
	_funcptr_glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)IntGetProcAddress("glMultiTexCoord2svARB");
	if(!_funcptr_glMultiTexCoord2svARB) ++numFailed;
	_funcptr_glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)IntGetProcAddress("glMultiTexCoord3dARB");
	if(!_funcptr_glMultiTexCoord3dARB) ++numFailed;
	_funcptr_glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)IntGetProcAddress("glMultiTexCoord3dvARB");
	if(!_funcptr_glMultiTexCoord3dvARB) ++numFailed;
	_funcptr_glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)IntGetProcAddress("glMultiTexCoord3fARB");
	if(!_funcptr_glMultiTexCoord3fARB) ++numFailed;
	_funcptr_glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)IntGetProcAddress("glMultiTexCoord3fvARB");
	if(!_funcptr_glMultiTexCoord3fvARB) ++numFailed;
	_funcptr_glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)IntGetProcAddress("glMultiTexCoord3iARB");
	if(!_funcptr_glMultiTexCoord3iARB) ++numFailed;
	_funcptr_glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)IntGetProcAddress("glMultiTexCoord3ivARB");
	if(!_funcptr_glMultiTexCoord3ivARB) ++numFailed;
	_funcptr_glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)IntGetProcAddress("glMultiTexCoord3sARB");
	if(!_funcptr_glMultiTexCoord3sARB) ++numFailed;
	_funcptr_glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)IntGetProcAddress("glMultiTexCoord3svARB");
	if(!_funcptr_glMultiTexCoord3svARB) ++numFailed;
	_funcptr_glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)IntGetProcAddress("glMultiTexCoord4dARB");
	if(!_funcptr_glMultiTexCoord4dARB) ++numFailed;
	_funcptr_glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)IntGetProcAddress("glMultiTexCoord4dvARB");
	if(!_funcptr_glMultiTexCoord4dvARB) ++numFailed;
	_funcptr_glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)IntGetProcAddress("glMultiTexCoord4fARB");
	if(!_funcptr_glMultiTexCoord4fARB) ++numFailed;
	_funcptr_glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)IntGetProcAddress("glMultiTexCoord4fvARB");
	if(!_funcptr_glMultiTexCoord4fvARB) ++numFailed;
	_funcptr_glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)IntGetProcAddress("glMultiTexCoord4iARB");
	if(!_funcptr_glMultiTexCoord4iARB) ++numFailed;
	_funcptr_glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)IntGetProcAddress("glMultiTexCoord4ivARB");
	if(!_funcptr_glMultiTexCoord4ivARB) ++numFailed;
	_funcptr_glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)IntGetProcAddress("glMultiTexCoord4sARB");
	if(!_funcptr_glMultiTexCoord4sARB) ++numFailed;
	_funcptr_glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)IntGetProcAddress("glMultiTexCoord4svARB");
	if(!_funcptr_glMultiTexCoord4svARB) ++numFailed;
	return numFailed;
}