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
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4UINVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4INVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERSI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4UINVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4INVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERIIVNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetProgramEnvParameterIivNV ; 
 scalar_t__ _funcptr_glGetProgramEnvParameterIuivNV ; 
 scalar_t__ _funcptr_glGetProgramLocalParameterIivNV ; 
 scalar_t__ _funcptr_glGetProgramLocalParameterIuivNV ; 
 scalar_t__ _funcptr_glProgramEnvParameterI4iNV ; 
 scalar_t__ _funcptr_glProgramEnvParameterI4ivNV ; 
 scalar_t__ _funcptr_glProgramEnvParameterI4uiNV ; 
 scalar_t__ _funcptr_glProgramEnvParameterI4uivNV ; 
 scalar_t__ _funcptr_glProgramEnvParametersI4ivNV ; 
 scalar_t__ _funcptr_glProgramEnvParametersI4uivNV ; 
 scalar_t__ _funcptr_glProgramLocalParameterI4iNV ; 
 scalar_t__ _funcptr_glProgramLocalParameterI4ivNV ; 
 scalar_t__ _funcptr_glProgramLocalParameterI4uiNV ; 
 scalar_t__ _funcptr_glProgramLocalParameterI4uivNV ; 
 scalar_t__ _funcptr_glProgramLocalParametersI4ivNV ; 
 scalar_t__ _funcptr_glProgramLocalParametersI4uivNV ; 

__attribute__((used)) static int LoadExt_NV_gpu_program4()
{
	int numFailed = 0;
	_funcptr_glGetProgramEnvParameterIivNV = (PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)IntGetProcAddress("glGetProgramEnvParameterIivNV");
	if(!_funcptr_glGetProgramEnvParameterIivNV) ++numFailed;
	_funcptr_glGetProgramEnvParameterIuivNV = (PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)IntGetProcAddress("glGetProgramEnvParameterIuivNV");
	if(!_funcptr_glGetProgramEnvParameterIuivNV) ++numFailed;
	_funcptr_glGetProgramLocalParameterIivNV = (PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)IntGetProcAddress("glGetProgramLocalParameterIivNV");
	if(!_funcptr_glGetProgramLocalParameterIivNV) ++numFailed;
	_funcptr_glGetProgramLocalParameterIuivNV = (PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)IntGetProcAddress("glGetProgramLocalParameterIuivNV");
	if(!_funcptr_glGetProgramLocalParameterIuivNV) ++numFailed;
	_funcptr_glProgramEnvParameterI4iNV = (PFNGLPROGRAMENVPARAMETERI4INVPROC)IntGetProcAddress("glProgramEnvParameterI4iNV");
	if(!_funcptr_glProgramEnvParameterI4iNV) ++numFailed;
	_funcptr_glProgramEnvParameterI4ivNV = (PFNGLPROGRAMENVPARAMETERI4IVNVPROC)IntGetProcAddress("glProgramEnvParameterI4ivNV");
	if(!_funcptr_glProgramEnvParameterI4ivNV) ++numFailed;
	_funcptr_glProgramEnvParameterI4uiNV = (PFNGLPROGRAMENVPARAMETERI4UINVPROC)IntGetProcAddress("glProgramEnvParameterI4uiNV");
	if(!_funcptr_glProgramEnvParameterI4uiNV) ++numFailed;
	_funcptr_glProgramEnvParameterI4uivNV = (PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)IntGetProcAddress("glProgramEnvParameterI4uivNV");
	if(!_funcptr_glProgramEnvParameterI4uivNV) ++numFailed;
	_funcptr_glProgramEnvParametersI4ivNV = (PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)IntGetProcAddress("glProgramEnvParametersI4ivNV");
	if(!_funcptr_glProgramEnvParametersI4ivNV) ++numFailed;
	_funcptr_glProgramEnvParametersI4uivNV = (PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)IntGetProcAddress("glProgramEnvParametersI4uivNV");
	if(!_funcptr_glProgramEnvParametersI4uivNV) ++numFailed;
	_funcptr_glProgramLocalParameterI4iNV = (PFNGLPROGRAMLOCALPARAMETERI4INVPROC)IntGetProcAddress("glProgramLocalParameterI4iNV");
	if(!_funcptr_glProgramLocalParameterI4iNV) ++numFailed;
	_funcptr_glProgramLocalParameterI4ivNV = (PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)IntGetProcAddress("glProgramLocalParameterI4ivNV");
	if(!_funcptr_glProgramLocalParameterI4ivNV) ++numFailed;
	_funcptr_glProgramLocalParameterI4uiNV = (PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)IntGetProcAddress("glProgramLocalParameterI4uiNV");
	if(!_funcptr_glProgramLocalParameterI4uiNV) ++numFailed;
	_funcptr_glProgramLocalParameterI4uivNV = (PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)IntGetProcAddress("glProgramLocalParameterI4uivNV");
	if(!_funcptr_glProgramLocalParameterI4uivNV) ++numFailed;
	_funcptr_glProgramLocalParametersI4ivNV = (PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)IntGetProcAddress("glProgramLocalParametersI4ivNV");
	if(!_funcptr_glProgramLocalParametersI4ivNV) ++numFailed;
	_funcptr_glProgramLocalParametersI4uivNV = (PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)IntGetProcAddress("glProgramLocalParametersI4uivNV");
	if(!_funcptr_glProgramLocalParametersI4uivNV) ++numFailed;
	return numFailed;
}