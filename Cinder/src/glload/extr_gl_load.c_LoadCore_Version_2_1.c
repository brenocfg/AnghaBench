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
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X3FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X2FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X4FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X2FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X4FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X3FVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glUniformMatrix2x3fv ; 
 scalar_t__ _funcptr_glUniformMatrix2x4fv ; 
 scalar_t__ _funcptr_glUniformMatrix3x2fv ; 
 scalar_t__ _funcptr_glUniformMatrix3x4fv ; 
 scalar_t__ _funcptr_glUniformMatrix4x2fv ; 
 scalar_t__ _funcptr_glUniformMatrix4x3fv ; 

__attribute__((used)) static int LoadCore_Version_2_1()
{
	int numFailed = 0;
	_funcptr_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glUniformMatrix2x3fv");
	if(!_funcptr_glUniformMatrix2x3fv) ++numFailed;
	_funcptr_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glUniformMatrix2x4fv");
	if(!_funcptr_glUniformMatrix2x4fv) ++numFailed;
	_funcptr_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glUniformMatrix3x2fv");
	if(!_funcptr_glUniformMatrix3x2fv) ++numFailed;
	_funcptr_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glUniformMatrix3x4fv");
	if(!_funcptr_glUniformMatrix3x4fv) ++numFailed;
	_funcptr_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glUniformMatrix4x2fv");
	if(!_funcptr_glUniformMatrix4x2fv) ++numFailed;
	_funcptr_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glUniformMatrix4x3fv");
	if(!_funcptr_glUniformMatrix4x3fv) ++numFailed;
	return numFailed;
}