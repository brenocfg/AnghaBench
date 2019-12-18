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
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERIEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERFEXTPROC ;
typedef  scalar_t__ PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetPixelTransformParameterfvEXT ; 
 scalar_t__ _funcptr_glGetPixelTransformParameterivEXT ; 
 scalar_t__ _funcptr_glPixelTransformParameterfEXT ; 
 scalar_t__ _funcptr_glPixelTransformParameterfvEXT ; 
 scalar_t__ _funcptr_glPixelTransformParameteriEXT ; 
 scalar_t__ _funcptr_glPixelTransformParameterivEXT ; 

__attribute__((used)) static int LoadExt_EXT_pixel_transform()
{
	int numFailed = 0;
	_funcptr_glGetPixelTransformParameterfvEXT = (PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC)IntGetProcAddress("glGetPixelTransformParameterfvEXT");
	if(!_funcptr_glGetPixelTransformParameterfvEXT) ++numFailed;
	_funcptr_glGetPixelTransformParameterivEXT = (PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC)IntGetProcAddress("glGetPixelTransformParameterivEXT");
	if(!_funcptr_glGetPixelTransformParameterivEXT) ++numFailed;
	_funcptr_glPixelTransformParameterfEXT = (PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)IntGetProcAddress("glPixelTransformParameterfEXT");
	if(!_funcptr_glPixelTransformParameterfEXT) ++numFailed;
	_funcptr_glPixelTransformParameterfvEXT = (PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)IntGetProcAddress("glPixelTransformParameterfvEXT");
	if(!_funcptr_glPixelTransformParameterfvEXT) ++numFailed;
	_funcptr_glPixelTransformParameteriEXT = (PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)IntGetProcAddress("glPixelTransformParameteriEXT");
	if(!_funcptr_glPixelTransformParameteriEXT) ++numFailed;
	_funcptr_glPixelTransformParameterivEXT = (PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)IntGetProcAddress("glPixelTransformParameterivEXT");
	if(!_funcptr_glPixelTransformParameterivEXT) ++numFailed;
	return numFailed;
}