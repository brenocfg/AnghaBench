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
typedef  scalar_t__ PFNGLTANGENTPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3SVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3SEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3IVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3IEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3FVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3FEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3DVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3DEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3BVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3BEXTPROC ;
typedef  scalar_t__ PFNGLBINORMALPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3SVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3SEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3IVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3IEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3FVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3FEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3DVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3DEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3BVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3BEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBinormal3bEXT ; 
 scalar_t__ _funcptr_glBinormal3bvEXT ; 
 scalar_t__ _funcptr_glBinormal3dEXT ; 
 scalar_t__ _funcptr_glBinormal3dvEXT ; 
 scalar_t__ _funcptr_glBinormal3fEXT ; 
 scalar_t__ _funcptr_glBinormal3fvEXT ; 
 scalar_t__ _funcptr_glBinormal3iEXT ; 
 scalar_t__ _funcptr_glBinormal3ivEXT ; 
 scalar_t__ _funcptr_glBinormal3sEXT ; 
 scalar_t__ _funcptr_glBinormal3svEXT ; 
 scalar_t__ _funcptr_glBinormalPointerEXT ; 
 scalar_t__ _funcptr_glTangent3bEXT ; 
 scalar_t__ _funcptr_glTangent3bvEXT ; 
 scalar_t__ _funcptr_glTangent3dEXT ; 
 scalar_t__ _funcptr_glTangent3dvEXT ; 
 scalar_t__ _funcptr_glTangent3fEXT ; 
 scalar_t__ _funcptr_glTangent3fvEXT ; 
 scalar_t__ _funcptr_glTangent3iEXT ; 
 scalar_t__ _funcptr_glTangent3ivEXT ; 
 scalar_t__ _funcptr_glTangent3sEXT ; 
 scalar_t__ _funcptr_glTangent3svEXT ; 
 scalar_t__ _funcptr_glTangentPointerEXT ; 

__attribute__((used)) static int LoadExt_EXT_coordinate_frame()
{
	int numFailed = 0;
	_funcptr_glBinormal3bEXT = (PFNGLBINORMAL3BEXTPROC)IntGetProcAddress("glBinormal3bEXT");
	if(!_funcptr_glBinormal3bEXT) ++numFailed;
	_funcptr_glBinormal3bvEXT = (PFNGLBINORMAL3BVEXTPROC)IntGetProcAddress("glBinormal3bvEXT");
	if(!_funcptr_glBinormal3bvEXT) ++numFailed;
	_funcptr_glBinormal3dEXT = (PFNGLBINORMAL3DEXTPROC)IntGetProcAddress("glBinormal3dEXT");
	if(!_funcptr_glBinormal3dEXT) ++numFailed;
	_funcptr_glBinormal3dvEXT = (PFNGLBINORMAL3DVEXTPROC)IntGetProcAddress("glBinormal3dvEXT");
	if(!_funcptr_glBinormal3dvEXT) ++numFailed;
	_funcptr_glBinormal3fEXT = (PFNGLBINORMAL3FEXTPROC)IntGetProcAddress("glBinormal3fEXT");
	if(!_funcptr_glBinormal3fEXT) ++numFailed;
	_funcptr_glBinormal3fvEXT = (PFNGLBINORMAL3FVEXTPROC)IntGetProcAddress("glBinormal3fvEXT");
	if(!_funcptr_glBinormal3fvEXT) ++numFailed;
	_funcptr_glBinormal3iEXT = (PFNGLBINORMAL3IEXTPROC)IntGetProcAddress("glBinormal3iEXT");
	if(!_funcptr_glBinormal3iEXT) ++numFailed;
	_funcptr_glBinormal3ivEXT = (PFNGLBINORMAL3IVEXTPROC)IntGetProcAddress("glBinormal3ivEXT");
	if(!_funcptr_glBinormal3ivEXT) ++numFailed;
	_funcptr_glBinormal3sEXT = (PFNGLBINORMAL3SEXTPROC)IntGetProcAddress("glBinormal3sEXT");
	if(!_funcptr_glBinormal3sEXT) ++numFailed;
	_funcptr_glBinormal3svEXT = (PFNGLBINORMAL3SVEXTPROC)IntGetProcAddress("glBinormal3svEXT");
	if(!_funcptr_glBinormal3svEXT) ++numFailed;
	_funcptr_glBinormalPointerEXT = (PFNGLBINORMALPOINTEREXTPROC)IntGetProcAddress("glBinormalPointerEXT");
	if(!_funcptr_glBinormalPointerEXT) ++numFailed;
	_funcptr_glTangent3bEXT = (PFNGLTANGENT3BEXTPROC)IntGetProcAddress("glTangent3bEXT");
	if(!_funcptr_glTangent3bEXT) ++numFailed;
	_funcptr_glTangent3bvEXT = (PFNGLTANGENT3BVEXTPROC)IntGetProcAddress("glTangent3bvEXT");
	if(!_funcptr_glTangent3bvEXT) ++numFailed;
	_funcptr_glTangent3dEXT = (PFNGLTANGENT3DEXTPROC)IntGetProcAddress("glTangent3dEXT");
	if(!_funcptr_glTangent3dEXT) ++numFailed;
	_funcptr_glTangent3dvEXT = (PFNGLTANGENT3DVEXTPROC)IntGetProcAddress("glTangent3dvEXT");
	if(!_funcptr_glTangent3dvEXT) ++numFailed;
	_funcptr_glTangent3fEXT = (PFNGLTANGENT3FEXTPROC)IntGetProcAddress("glTangent3fEXT");
	if(!_funcptr_glTangent3fEXT) ++numFailed;
	_funcptr_glTangent3fvEXT = (PFNGLTANGENT3FVEXTPROC)IntGetProcAddress("glTangent3fvEXT");
	if(!_funcptr_glTangent3fvEXT) ++numFailed;
	_funcptr_glTangent3iEXT = (PFNGLTANGENT3IEXTPROC)IntGetProcAddress("glTangent3iEXT");
	if(!_funcptr_glTangent3iEXT) ++numFailed;
	_funcptr_glTangent3ivEXT = (PFNGLTANGENT3IVEXTPROC)IntGetProcAddress("glTangent3ivEXT");
	if(!_funcptr_glTangent3ivEXT) ++numFailed;
	_funcptr_glTangent3sEXT = (PFNGLTANGENT3SEXTPROC)IntGetProcAddress("glTangent3sEXT");
	if(!_funcptr_glTangent3sEXT) ++numFailed;
	_funcptr_glTangent3svEXT = (PFNGLTANGENT3SVEXTPROC)IntGetProcAddress("glTangent3svEXT");
	if(!_funcptr_glTangent3svEXT) ++numFailed;
	_funcptr_glTangentPointerEXT = (PFNGLTANGENTPOINTEREXTPROC)IntGetProcAddress("glTangentPointerEXT");
	if(!_funcptr_glTangentPointerEXT) ++numFailed;
	return numFailed;
}