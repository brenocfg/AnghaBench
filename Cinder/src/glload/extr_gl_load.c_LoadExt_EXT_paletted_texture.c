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
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEEXTPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glColorTableEXT ; 
 scalar_t__ _funcptr_glGetColorTableEXT ; 
 scalar_t__ _funcptr_glGetColorTableParameterfvEXT ; 
 scalar_t__ _funcptr_glGetColorTableParameterivEXT ; 

__attribute__((used)) static int LoadExt_EXT_paletted_texture()
{
	int numFailed = 0;
	_funcptr_glColorTableEXT = (PFNGLCOLORTABLEEXTPROC)IntGetProcAddress("glColorTableEXT");
	if(!_funcptr_glColorTableEXT) ++numFailed;
	_funcptr_glGetColorTableEXT = (PFNGLGETCOLORTABLEEXTPROC)IntGetProcAddress("glGetColorTableEXT");
	if(!_funcptr_glGetColorTableEXT) ++numFailed;
	_funcptr_glGetColorTableParameterfvEXT = (PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)IntGetProcAddress("glGetColorTableParameterfvEXT");
	if(!_funcptr_glGetColorTableParameterfvEXT) ++numFailed;
	_funcptr_glGetColorTableParameterivEXT = (PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)IntGetProcAddress("glGetColorTableParameterivEXT");
	if(!_funcptr_glGetColorTableParameterivEXT) ++numFailed;
	return numFailed;
}