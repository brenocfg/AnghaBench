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
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMDVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetUniformdv ; 
 scalar_t__ _funcptr_glUniform1d ; 
 scalar_t__ _funcptr_glUniform1dv ; 
 scalar_t__ _funcptr_glUniform2d ; 
 scalar_t__ _funcptr_glUniform2dv ; 
 scalar_t__ _funcptr_glUniform3d ; 
 scalar_t__ _funcptr_glUniform3dv ; 
 scalar_t__ _funcptr_glUniform4d ; 
 scalar_t__ _funcptr_glUniform4dv ; 
 scalar_t__ _funcptr_glUniformMatrix2dv ; 
 scalar_t__ _funcptr_glUniformMatrix2x3dv ; 
 scalar_t__ _funcptr_glUniformMatrix2x4dv ; 
 scalar_t__ _funcptr_glUniformMatrix3dv ; 
 scalar_t__ _funcptr_glUniformMatrix3x2dv ; 
 scalar_t__ _funcptr_glUniformMatrix3x4dv ; 
 scalar_t__ _funcptr_glUniformMatrix4dv ; 
 scalar_t__ _funcptr_glUniformMatrix4x2dv ; 
 scalar_t__ _funcptr_glUniformMatrix4x3dv ; 

__attribute__((used)) static int LoadExt_ARB_gpu_shader_fp64()
{
	int numFailed = 0;
	_funcptr_glGetUniformdv = (PFNGLGETUNIFORMDVPROC)IntGetProcAddress("glGetUniformdv");
	if(!_funcptr_glGetUniformdv) ++numFailed;
	_funcptr_glUniform1d = (PFNGLUNIFORM1DPROC)IntGetProcAddress("glUniform1d");
	if(!_funcptr_glUniform1d) ++numFailed;
	_funcptr_glUniform1dv = (PFNGLUNIFORM1DVPROC)IntGetProcAddress("glUniform1dv");
	if(!_funcptr_glUniform1dv) ++numFailed;
	_funcptr_glUniform2d = (PFNGLUNIFORM2DPROC)IntGetProcAddress("glUniform2d");
	if(!_funcptr_glUniform2d) ++numFailed;
	_funcptr_glUniform2dv = (PFNGLUNIFORM2DVPROC)IntGetProcAddress("glUniform2dv");
	if(!_funcptr_glUniform2dv) ++numFailed;
	_funcptr_glUniform3d = (PFNGLUNIFORM3DPROC)IntGetProcAddress("glUniform3d");
	if(!_funcptr_glUniform3d) ++numFailed;
	_funcptr_glUniform3dv = (PFNGLUNIFORM3DVPROC)IntGetProcAddress("glUniform3dv");
	if(!_funcptr_glUniform3dv) ++numFailed;
	_funcptr_glUniform4d = (PFNGLUNIFORM4DPROC)IntGetProcAddress("glUniform4d");
	if(!_funcptr_glUniform4d) ++numFailed;
	_funcptr_glUniform4dv = (PFNGLUNIFORM4DVPROC)IntGetProcAddress("glUniform4dv");
	if(!_funcptr_glUniform4dv) ++numFailed;
	_funcptr_glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)IntGetProcAddress("glUniformMatrix2dv");
	if(!_funcptr_glUniformMatrix2dv) ++numFailed;
	_funcptr_glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)IntGetProcAddress("glUniformMatrix2x3dv");
	if(!_funcptr_glUniformMatrix2x3dv) ++numFailed;
	_funcptr_glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)IntGetProcAddress("glUniformMatrix2x4dv");
	if(!_funcptr_glUniformMatrix2x4dv) ++numFailed;
	_funcptr_glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)IntGetProcAddress("glUniformMatrix3dv");
	if(!_funcptr_glUniformMatrix3dv) ++numFailed;
	_funcptr_glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)IntGetProcAddress("glUniformMatrix3x2dv");
	if(!_funcptr_glUniformMatrix3x2dv) ++numFailed;
	_funcptr_glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)IntGetProcAddress("glUniformMatrix3x4dv");
	if(!_funcptr_glUniformMatrix3x4dv) ++numFailed;
	_funcptr_glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)IntGetProcAddress("glUniformMatrix4dv");
	if(!_funcptr_glUniformMatrix4dv) ++numFailed;
	_funcptr_glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)IntGetProcAddress("glUniformMatrix4x2dv");
	if(!_funcptr_glUniformMatrix4x2dv) ++numFailed;
	_funcptr_glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)IntGetProcAddress("glUniformMatrix4x3dv");
	if(!_funcptr_glUniformMatrix4x3dv) ++numFailed;
	return numFailed;
}