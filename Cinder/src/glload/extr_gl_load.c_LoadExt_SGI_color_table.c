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
typedef  scalar_t__ PFNGLGETCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERIVSGIPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERFVSGIPROC ;
typedef  scalar_t__ PFNGLCOPYCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERIVSGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERFVSGIPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glColorTableParameterfvSGI ; 
 scalar_t__ _funcptr_glColorTableParameterivSGI ; 
 scalar_t__ _funcptr_glColorTableSGI ; 
 scalar_t__ _funcptr_glCopyColorTableSGI ; 
 scalar_t__ _funcptr_glGetColorTableParameterfvSGI ; 
 scalar_t__ _funcptr_glGetColorTableParameterivSGI ; 
 scalar_t__ _funcptr_glGetColorTableSGI ; 

__attribute__((used)) static int LoadExt_SGI_color_table()
{
	int numFailed = 0;
	_funcptr_glColorTableParameterfvSGI = (PFNGLCOLORTABLEPARAMETERFVSGIPROC)IntGetProcAddress("glColorTableParameterfvSGI");
	if(!_funcptr_glColorTableParameterfvSGI) ++numFailed;
	_funcptr_glColorTableParameterivSGI = (PFNGLCOLORTABLEPARAMETERIVSGIPROC)IntGetProcAddress("glColorTableParameterivSGI");
	if(!_funcptr_glColorTableParameterivSGI) ++numFailed;
	_funcptr_glColorTableSGI = (PFNGLCOLORTABLESGIPROC)IntGetProcAddress("glColorTableSGI");
	if(!_funcptr_glColorTableSGI) ++numFailed;
	_funcptr_glCopyColorTableSGI = (PFNGLCOPYCOLORTABLESGIPROC)IntGetProcAddress("glCopyColorTableSGI");
	if(!_funcptr_glCopyColorTableSGI) ++numFailed;
	_funcptr_glGetColorTableParameterfvSGI = (PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)IntGetProcAddress("glGetColorTableParameterfvSGI");
	if(!_funcptr_glGetColorTableParameterfvSGI) ++numFailed;
	_funcptr_glGetColorTableParameterivSGI = (PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)IntGetProcAddress("glGetColorTableParameterivSGI");
	if(!_funcptr_glGetColorTableParameterivSGI) ++numFailed;
	_funcptr_glGetColorTableSGI = (PFNGLGETCOLORTABLESGIPROC)IntGetProcAddress("glGetColorTableSGI");
	if(!_funcptr_glGetColorTableSGI) ++numFailed;
	return numFailed;
}