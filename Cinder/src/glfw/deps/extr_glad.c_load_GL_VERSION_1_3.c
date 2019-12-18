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
typedef  scalar_t__ PFNGLSAMPLECOVERAGEPROC ;
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
typedef  scalar_t__ PFNGLGETCOMPRESSEDTEXIMAGEPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVETEXTUREPROC ;
typedef  scalar_t__ PFNGLACTIVETEXTUREPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_3 ; 
 scalar_t__ glad_glActiveTexture ; 
 scalar_t__ glad_glClientActiveTexture ; 
 scalar_t__ glad_glCompressedTexImage1D ; 
 scalar_t__ glad_glCompressedTexImage2D ; 
 scalar_t__ glad_glCompressedTexImage3D ; 
 scalar_t__ glad_glCompressedTexSubImage1D ; 
 scalar_t__ glad_glCompressedTexSubImage2D ; 
 scalar_t__ glad_glCompressedTexSubImage3D ; 
 scalar_t__ glad_glGetCompressedTexImage ; 
 scalar_t__ glad_glLoadTransposeMatrixd ; 
 scalar_t__ glad_glLoadTransposeMatrixf ; 
 scalar_t__ glad_glMultTransposeMatrixd ; 
 scalar_t__ glad_glMultTransposeMatrixf ; 
 scalar_t__ glad_glMultiTexCoord1d ; 
 scalar_t__ glad_glMultiTexCoord1dv ; 
 scalar_t__ glad_glMultiTexCoord1f ; 
 scalar_t__ glad_glMultiTexCoord1fv ; 
 scalar_t__ glad_glMultiTexCoord1i ; 
 scalar_t__ glad_glMultiTexCoord1iv ; 
 scalar_t__ glad_glMultiTexCoord1s ; 
 scalar_t__ glad_glMultiTexCoord1sv ; 
 scalar_t__ glad_glMultiTexCoord2d ; 
 scalar_t__ glad_glMultiTexCoord2dv ; 
 scalar_t__ glad_glMultiTexCoord2f ; 
 scalar_t__ glad_glMultiTexCoord2fv ; 
 scalar_t__ glad_glMultiTexCoord2i ; 
 scalar_t__ glad_glMultiTexCoord2iv ; 
 scalar_t__ glad_glMultiTexCoord2s ; 
 scalar_t__ glad_glMultiTexCoord2sv ; 
 scalar_t__ glad_glMultiTexCoord3d ; 
 scalar_t__ glad_glMultiTexCoord3dv ; 
 scalar_t__ glad_glMultiTexCoord3f ; 
 scalar_t__ glad_glMultiTexCoord3fv ; 
 scalar_t__ glad_glMultiTexCoord3i ; 
 scalar_t__ glad_glMultiTexCoord3iv ; 
 scalar_t__ glad_glMultiTexCoord3s ; 
 scalar_t__ glad_glMultiTexCoord3sv ; 
 scalar_t__ glad_glMultiTexCoord4d ; 
 scalar_t__ glad_glMultiTexCoord4dv ; 
 scalar_t__ glad_glMultiTexCoord4f ; 
 scalar_t__ glad_glMultiTexCoord4fv ; 
 scalar_t__ glad_glMultiTexCoord4i ; 
 scalar_t__ glad_glMultiTexCoord4iv ; 
 scalar_t__ glad_glMultiTexCoord4s ; 
 scalar_t__ glad_glMultiTexCoord4sv ; 
 scalar_t__ glad_glSampleCoverage ; 

__attribute__((used)) static void load_GL_VERSION_1_3(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_3) return;
	glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
	glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)load("glSampleCoverage");
	glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)load("glCompressedTexImage3D");
	glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)load("glCompressedTexImage2D");
	glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)load("glCompressedTexImage1D");
	glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)load("glCompressedTexSubImage3D");
	glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)load("glCompressedTexSubImage2D");
	glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)load("glCompressedTexSubImage1D");
	glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)load("glGetCompressedTexImage");
	glad_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)load("glClientActiveTexture");
	glad_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)load("glMultiTexCoord1d");
	glad_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)load("glMultiTexCoord1dv");
	glad_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)load("glMultiTexCoord1f");
	glad_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)load("glMultiTexCoord1fv");
	glad_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)load("glMultiTexCoord1i");
	glad_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)load("glMultiTexCoord1iv");
	glad_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)load("glMultiTexCoord1s");
	glad_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)load("glMultiTexCoord1sv");
	glad_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)load("glMultiTexCoord2d");
	glad_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)load("glMultiTexCoord2dv");
	glad_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)load("glMultiTexCoord2f");
	glad_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)load("glMultiTexCoord2fv");
	glad_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)load("glMultiTexCoord2i");
	glad_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)load("glMultiTexCoord2iv");
	glad_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)load("glMultiTexCoord2s");
	glad_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)load("glMultiTexCoord2sv");
	glad_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)load("glMultiTexCoord3d");
	glad_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)load("glMultiTexCoord3dv");
	glad_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)load("glMultiTexCoord3f");
	glad_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)load("glMultiTexCoord3fv");
	glad_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)load("glMultiTexCoord3i");
	glad_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)load("glMultiTexCoord3iv");
	glad_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)load("glMultiTexCoord3s");
	glad_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)load("glMultiTexCoord3sv");
	glad_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)load("glMultiTexCoord4d");
	glad_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)load("glMultiTexCoord4dv");
	glad_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)load("glMultiTexCoord4f");
	glad_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)load("glMultiTexCoord4fv");
	glad_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)load("glMultiTexCoord4i");
	glad_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)load("glMultiTexCoord4iv");
	glad_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)load("glMultiTexCoord4s");
	glad_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)load("glMultiTexCoord4sv");
	glad_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)load("glLoadTransposeMatrixf");
	glad_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)load("glLoadTransposeMatrixd");
	glad_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)load("glMultTransposeMatrixf");
	glad_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)load("glMultTransposeMatrixd");
}