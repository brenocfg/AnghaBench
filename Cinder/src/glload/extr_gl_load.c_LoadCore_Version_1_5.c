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
typedef  scalar_t__ PFNGLUNMAPBUFFERPROC ;
typedef  scalar_t__ PFNGLMAPBUFFERPROC ;
typedef  scalar_t__ PFNGLISQUERYPROC ;
typedef  scalar_t__ PFNGLISBUFFERPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTUIVPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTIVPROC ;
typedef  scalar_t__ PFNGLGETQUERYIVPROC ;
typedef  scalar_t__ PFNGLGETBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPOINTERVPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGENQUERIESPROC ;
typedef  scalar_t__ PFNGLGENBUFFERSPROC ;
typedef  scalar_t__ PFNGLENDQUERYPROC ;
typedef  scalar_t__ PFNGLDELETEQUERIESPROC ;
typedef  scalar_t__ PFNGLDELETEBUFFERSPROC ;
typedef  scalar_t__ PFNGLBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLBUFFERDATAPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginQuery ; 
 scalar_t__ _funcptr_glBindBuffer ; 
 scalar_t__ _funcptr_glBufferData ; 
 scalar_t__ _funcptr_glBufferSubData ; 
 scalar_t__ _funcptr_glDeleteBuffers ; 
 scalar_t__ _funcptr_glDeleteQueries ; 
 scalar_t__ _funcptr_glEndQuery ; 
 scalar_t__ _funcptr_glGenBuffers ; 
 scalar_t__ _funcptr_glGenQueries ; 
 scalar_t__ _funcptr_glGetBufferParameteriv ; 
 scalar_t__ _funcptr_glGetBufferPointerv ; 
 scalar_t__ _funcptr_glGetBufferSubData ; 
 scalar_t__ _funcptr_glGetQueryObjectiv ; 
 scalar_t__ _funcptr_glGetQueryObjectuiv ; 
 scalar_t__ _funcptr_glGetQueryiv ; 
 scalar_t__ _funcptr_glIsBuffer ; 
 scalar_t__ _funcptr_glIsQuery ; 
 scalar_t__ _funcptr_glMapBuffer ; 
 scalar_t__ _funcptr_glUnmapBuffer ; 

__attribute__((used)) static int LoadCore_Version_1_5()
{
	int numFailed = 0;
	_funcptr_glBeginQuery = (PFNGLBEGINQUERYPROC)IntGetProcAddress("glBeginQuery");
	if(!_funcptr_glBeginQuery) ++numFailed;
	_funcptr_glBindBuffer = (PFNGLBINDBUFFERPROC)IntGetProcAddress("glBindBuffer");
	if(!_funcptr_glBindBuffer) ++numFailed;
	_funcptr_glBufferData = (PFNGLBUFFERDATAPROC)IntGetProcAddress("glBufferData");
	if(!_funcptr_glBufferData) ++numFailed;
	_funcptr_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)IntGetProcAddress("glBufferSubData");
	if(!_funcptr_glBufferSubData) ++numFailed;
	_funcptr_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)IntGetProcAddress("glDeleteBuffers");
	if(!_funcptr_glDeleteBuffers) ++numFailed;
	_funcptr_glDeleteQueries = (PFNGLDELETEQUERIESPROC)IntGetProcAddress("glDeleteQueries");
	if(!_funcptr_glDeleteQueries) ++numFailed;
	_funcptr_glEndQuery = (PFNGLENDQUERYPROC)IntGetProcAddress("glEndQuery");
	if(!_funcptr_glEndQuery) ++numFailed;
	_funcptr_glGenBuffers = (PFNGLGENBUFFERSPROC)IntGetProcAddress("glGenBuffers");
	if(!_funcptr_glGenBuffers) ++numFailed;
	_funcptr_glGenQueries = (PFNGLGENQUERIESPROC)IntGetProcAddress("glGenQueries");
	if(!_funcptr_glGenQueries) ++numFailed;
	_funcptr_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetBufferParameteriv");
	if(!_funcptr_glGetBufferParameteriv) ++numFailed;
	_funcptr_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)IntGetProcAddress("glGetBufferPointerv");
	if(!_funcptr_glGetBufferPointerv) ++numFailed;
	_funcptr_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)IntGetProcAddress("glGetBufferSubData");
	if(!_funcptr_glGetBufferSubData) ++numFailed;
	_funcptr_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)IntGetProcAddress("glGetQueryObjectiv");
	if(!_funcptr_glGetQueryObjectiv) ++numFailed;
	_funcptr_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)IntGetProcAddress("glGetQueryObjectuiv");
	if(!_funcptr_glGetQueryObjectuiv) ++numFailed;
	_funcptr_glGetQueryiv = (PFNGLGETQUERYIVPROC)IntGetProcAddress("glGetQueryiv");
	if(!_funcptr_glGetQueryiv) ++numFailed;
	_funcptr_glIsBuffer = (PFNGLISBUFFERPROC)IntGetProcAddress("glIsBuffer");
	if(!_funcptr_glIsBuffer) ++numFailed;
	_funcptr_glIsQuery = (PFNGLISQUERYPROC)IntGetProcAddress("glIsQuery");
	if(!_funcptr_glIsQuery) ++numFailed;
	_funcptr_glMapBuffer = (PFNGLMAPBUFFERPROC)IntGetProcAddress("glMapBuffer");
	if(!_funcptr_glMapBuffer) ++numFailed;
	_funcptr_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)IntGetProcAddress("glUnmapBuffer");
	if(!_funcptr_glUnmapBuffer) ++numFailed;
	return numFailed;
}