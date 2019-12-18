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
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXFPROC ;
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXDPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXFPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXDPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVETEXTUREPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glClientActiveTexture ; 
 scalar_t__ _funcptr_glLoadTransposeMatrixd ; 
 scalar_t__ _funcptr_glLoadTransposeMatrixf ; 
 scalar_t__ _funcptr_glMultTransposeMatrixd ; 
 scalar_t__ _funcptr_glMultTransposeMatrixf ; 
 scalar_t__ _funcptr_glMultiTexCoord1d ; 
 scalar_t__ _funcptr_glMultiTexCoord1dv ; 
 scalar_t__ _funcptr_glMultiTexCoord1f ; 
 scalar_t__ _funcptr_glMultiTexCoord1fv ; 
 scalar_t__ _funcptr_glMultiTexCoord1i ; 
 scalar_t__ _funcptr_glMultiTexCoord1iv ; 
 scalar_t__ _funcptr_glMultiTexCoord1s ; 
 scalar_t__ _funcptr_glMultiTexCoord1sv ; 
 scalar_t__ _funcptr_glMultiTexCoord2d ; 
 scalar_t__ _funcptr_glMultiTexCoord2dv ; 
 scalar_t__ _funcptr_glMultiTexCoord2f ; 
 scalar_t__ _funcptr_glMultiTexCoord2fv ; 
 scalar_t__ _funcptr_glMultiTexCoord2i ; 
 scalar_t__ _funcptr_glMultiTexCoord2iv ; 
 scalar_t__ _funcptr_glMultiTexCoord2s ; 
 scalar_t__ _funcptr_glMultiTexCoord2sv ; 
 scalar_t__ _funcptr_glMultiTexCoord3d ; 
 scalar_t__ _funcptr_glMultiTexCoord3dv ; 
 scalar_t__ _funcptr_glMultiTexCoord3f ; 
 scalar_t__ _funcptr_glMultiTexCoord3fv ; 
 scalar_t__ _funcptr_glMultiTexCoord3i ; 
 scalar_t__ _funcptr_glMultiTexCoord3iv ; 
 scalar_t__ _funcptr_glMultiTexCoord3s ; 
 scalar_t__ _funcptr_glMultiTexCoord3sv ; 
 scalar_t__ _funcptr_glMultiTexCoord4d ; 
 scalar_t__ _funcptr_glMultiTexCoord4dv ; 
 scalar_t__ _funcptr_glMultiTexCoord4f ; 
 scalar_t__ _funcptr_glMultiTexCoord4fv ; 
 scalar_t__ _funcptr_glMultiTexCoord4i ; 
 scalar_t__ _funcptr_glMultiTexCoord4iv ; 
 scalar_t__ _funcptr_glMultiTexCoord4s ; 
 scalar_t__ _funcptr_glMultiTexCoord4sv ; 

__attribute__((used)) static int LoadCore_Version_1_3_Comp()
{
	int numFailed = 0;
	_funcptr_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)IntGetProcAddress("glClientActiveTexture");
	if(!_funcptr_glClientActiveTexture) ++numFailed;
	_funcptr_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)IntGetProcAddress("glLoadTransposeMatrixd");
	if(!_funcptr_glLoadTransposeMatrixd) ++numFailed;
	_funcptr_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)IntGetProcAddress("glLoadTransposeMatrixf");
	if(!_funcptr_glLoadTransposeMatrixf) ++numFailed;
	_funcptr_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)IntGetProcAddress("glMultTransposeMatrixd");
	if(!_funcptr_glMultTransposeMatrixd) ++numFailed;
	_funcptr_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)IntGetProcAddress("glMultTransposeMatrixf");
	if(!_funcptr_glMultTransposeMatrixf) ++numFailed;
	_funcptr_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)IntGetProcAddress("glMultiTexCoord1d");
	if(!_funcptr_glMultiTexCoord1d) ++numFailed;
	_funcptr_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)IntGetProcAddress("glMultiTexCoord1dv");
	if(!_funcptr_glMultiTexCoord1dv) ++numFailed;
	_funcptr_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)IntGetProcAddress("glMultiTexCoord1f");
	if(!_funcptr_glMultiTexCoord1f) ++numFailed;
	_funcptr_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)IntGetProcAddress("glMultiTexCoord1fv");
	if(!_funcptr_glMultiTexCoord1fv) ++numFailed;
	_funcptr_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)IntGetProcAddress("glMultiTexCoord1i");
	if(!_funcptr_glMultiTexCoord1i) ++numFailed;
	_funcptr_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)IntGetProcAddress("glMultiTexCoord1iv");
	if(!_funcptr_glMultiTexCoord1iv) ++numFailed;
	_funcptr_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)IntGetProcAddress("glMultiTexCoord1s");
	if(!_funcptr_glMultiTexCoord1s) ++numFailed;
	_funcptr_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)IntGetProcAddress("glMultiTexCoord1sv");
	if(!_funcptr_glMultiTexCoord1sv) ++numFailed;
	_funcptr_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)IntGetProcAddress("glMultiTexCoord2d");
	if(!_funcptr_glMultiTexCoord2d) ++numFailed;
	_funcptr_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)IntGetProcAddress("glMultiTexCoord2dv");
	if(!_funcptr_glMultiTexCoord2dv) ++numFailed;
	_funcptr_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)IntGetProcAddress("glMultiTexCoord2f");
	if(!_funcptr_glMultiTexCoord2f) ++numFailed;
	_funcptr_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)IntGetProcAddress("glMultiTexCoord2fv");
	if(!_funcptr_glMultiTexCoord2fv) ++numFailed;
	_funcptr_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)IntGetProcAddress("glMultiTexCoord2i");
	if(!_funcptr_glMultiTexCoord2i) ++numFailed;
	_funcptr_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)IntGetProcAddress("glMultiTexCoord2iv");
	if(!_funcptr_glMultiTexCoord2iv) ++numFailed;
	_funcptr_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)IntGetProcAddress("glMultiTexCoord2s");
	if(!_funcptr_glMultiTexCoord2s) ++numFailed;
	_funcptr_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)IntGetProcAddress("glMultiTexCoord2sv");
	if(!_funcptr_glMultiTexCoord2sv) ++numFailed;
	_funcptr_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)IntGetProcAddress("glMultiTexCoord3d");
	if(!_funcptr_glMultiTexCoord3d) ++numFailed;
	_funcptr_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)IntGetProcAddress("glMultiTexCoord3dv");
	if(!_funcptr_glMultiTexCoord3dv) ++numFailed;
	_funcptr_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)IntGetProcAddress("glMultiTexCoord3f");
	if(!_funcptr_glMultiTexCoord3f) ++numFailed;
	_funcptr_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)IntGetProcAddress("glMultiTexCoord3fv");
	if(!_funcptr_glMultiTexCoord3fv) ++numFailed;
	_funcptr_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)IntGetProcAddress("glMultiTexCoord3i");
	if(!_funcptr_glMultiTexCoord3i) ++numFailed;
	_funcptr_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)IntGetProcAddress("glMultiTexCoord3iv");
	if(!_funcptr_glMultiTexCoord3iv) ++numFailed;
	_funcptr_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)IntGetProcAddress("glMultiTexCoord3s");
	if(!_funcptr_glMultiTexCoord3s) ++numFailed;
	_funcptr_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)IntGetProcAddress("glMultiTexCoord3sv");
	if(!_funcptr_glMultiTexCoord3sv) ++numFailed;
	_funcptr_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)IntGetProcAddress("glMultiTexCoord4d");
	if(!_funcptr_glMultiTexCoord4d) ++numFailed;
	_funcptr_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)IntGetProcAddress("glMultiTexCoord4dv");
	if(!_funcptr_glMultiTexCoord4dv) ++numFailed;
	_funcptr_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)IntGetProcAddress("glMultiTexCoord4f");
	if(!_funcptr_glMultiTexCoord4f) ++numFailed;
	_funcptr_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)IntGetProcAddress("glMultiTexCoord4fv");
	if(!_funcptr_glMultiTexCoord4fv) ++numFailed;
	_funcptr_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)IntGetProcAddress("glMultiTexCoord4i");
	if(!_funcptr_glMultiTexCoord4i) ++numFailed;
	_funcptr_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)IntGetProcAddress("glMultiTexCoord4iv");
	if(!_funcptr_glMultiTexCoord4iv) ++numFailed;
	_funcptr_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)IntGetProcAddress("glMultiTexCoord4s");
	if(!_funcptr_glMultiTexCoord4s) ++numFailed;
	_funcptr_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)IntGetProcAddress("glMultiTexCoord4sv");
	if(!_funcptr_glMultiTexCoord4sv) ++numFailed;
	return numFailed;
}