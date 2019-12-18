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
typedef  scalar_t__ PFNGLSECONDARYCOLORPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3USVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3USEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UIVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UIEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UBVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UBEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3SVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3SEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3IVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3IEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3FVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3FEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3DVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3DEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3BVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3BEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glSecondaryColor3bEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3bvEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3dEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3dvEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3fEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3fvEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3iEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3ivEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3sEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3svEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3ubEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3ubvEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3uiEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3uivEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3usEXT ; 
 scalar_t__ _funcptr_glSecondaryColor3usvEXT ; 
 scalar_t__ _funcptr_glSecondaryColorPointerEXT ; 

__attribute__((used)) static int LoadExt_EXT_secondary_color()
{
	int numFailed = 0;
	_funcptr_glSecondaryColor3bEXT = (PFNGLSECONDARYCOLOR3BEXTPROC)IntGetProcAddress("glSecondaryColor3bEXT");
	if(!_funcptr_glSecondaryColor3bEXT) ++numFailed;
	_funcptr_glSecondaryColor3bvEXT = (PFNGLSECONDARYCOLOR3BVEXTPROC)IntGetProcAddress("glSecondaryColor3bvEXT");
	if(!_funcptr_glSecondaryColor3bvEXT) ++numFailed;
	_funcptr_glSecondaryColor3dEXT = (PFNGLSECONDARYCOLOR3DEXTPROC)IntGetProcAddress("glSecondaryColor3dEXT");
	if(!_funcptr_glSecondaryColor3dEXT) ++numFailed;
	_funcptr_glSecondaryColor3dvEXT = (PFNGLSECONDARYCOLOR3DVEXTPROC)IntGetProcAddress("glSecondaryColor3dvEXT");
	if(!_funcptr_glSecondaryColor3dvEXT) ++numFailed;
	_funcptr_glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC)IntGetProcAddress("glSecondaryColor3fEXT");
	if(!_funcptr_glSecondaryColor3fEXT) ++numFailed;
	_funcptr_glSecondaryColor3fvEXT = (PFNGLSECONDARYCOLOR3FVEXTPROC)IntGetProcAddress("glSecondaryColor3fvEXT");
	if(!_funcptr_glSecondaryColor3fvEXT) ++numFailed;
	_funcptr_glSecondaryColor3iEXT = (PFNGLSECONDARYCOLOR3IEXTPROC)IntGetProcAddress("glSecondaryColor3iEXT");
	if(!_funcptr_glSecondaryColor3iEXT) ++numFailed;
	_funcptr_glSecondaryColor3ivEXT = (PFNGLSECONDARYCOLOR3IVEXTPROC)IntGetProcAddress("glSecondaryColor3ivEXT");
	if(!_funcptr_glSecondaryColor3ivEXT) ++numFailed;
	_funcptr_glSecondaryColor3sEXT = (PFNGLSECONDARYCOLOR3SEXTPROC)IntGetProcAddress("glSecondaryColor3sEXT");
	if(!_funcptr_glSecondaryColor3sEXT) ++numFailed;
	_funcptr_glSecondaryColor3svEXT = (PFNGLSECONDARYCOLOR3SVEXTPROC)IntGetProcAddress("glSecondaryColor3svEXT");
	if(!_funcptr_glSecondaryColor3svEXT) ++numFailed;
	_funcptr_glSecondaryColor3ubEXT = (PFNGLSECONDARYCOLOR3UBEXTPROC)IntGetProcAddress("glSecondaryColor3ubEXT");
	if(!_funcptr_glSecondaryColor3ubEXT) ++numFailed;
	_funcptr_glSecondaryColor3ubvEXT = (PFNGLSECONDARYCOLOR3UBVEXTPROC)IntGetProcAddress("glSecondaryColor3ubvEXT");
	if(!_funcptr_glSecondaryColor3ubvEXT) ++numFailed;
	_funcptr_glSecondaryColor3uiEXT = (PFNGLSECONDARYCOLOR3UIEXTPROC)IntGetProcAddress("glSecondaryColor3uiEXT");
	if(!_funcptr_glSecondaryColor3uiEXT) ++numFailed;
	_funcptr_glSecondaryColor3uivEXT = (PFNGLSECONDARYCOLOR3UIVEXTPROC)IntGetProcAddress("glSecondaryColor3uivEXT");
	if(!_funcptr_glSecondaryColor3uivEXT) ++numFailed;
	_funcptr_glSecondaryColor3usEXT = (PFNGLSECONDARYCOLOR3USEXTPROC)IntGetProcAddress("glSecondaryColor3usEXT");
	if(!_funcptr_glSecondaryColor3usEXT) ++numFailed;
	_funcptr_glSecondaryColor3usvEXT = (PFNGLSECONDARYCOLOR3USVEXTPROC)IntGetProcAddress("glSecondaryColor3usvEXT");
	if(!_funcptr_glSecondaryColor3usvEXT) ++numFailed;
	_funcptr_glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC)IntGetProcAddress("glSecondaryColorPointerEXT");
	if(!_funcptr_glSecondaryColorPointerEXT) ++numFailed;
	return numFailed;
}