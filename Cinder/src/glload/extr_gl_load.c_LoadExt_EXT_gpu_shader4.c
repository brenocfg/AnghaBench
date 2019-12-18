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
typedef  scalar_t__ PFNGLUNIFORM4UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM4UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UIEXTPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMUIVEXTPROC ;
typedef  scalar_t__ PFNGLGETFRAGDATALOCATIONEXTPROC ;
typedef  scalar_t__ PFNGLBINDFRAGDATALOCATIONEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindFragDataLocationEXT ; 
 scalar_t__ _funcptr_glGetFragDataLocationEXT ; 
 scalar_t__ _funcptr_glGetUniformuivEXT ; 
 scalar_t__ _funcptr_glUniform1uiEXT ; 
 scalar_t__ _funcptr_glUniform1uivEXT ; 
 scalar_t__ _funcptr_glUniform2uiEXT ; 
 scalar_t__ _funcptr_glUniform2uivEXT ; 
 scalar_t__ _funcptr_glUniform3uiEXT ; 
 scalar_t__ _funcptr_glUniform3uivEXT ; 
 scalar_t__ _funcptr_glUniform4uiEXT ; 
 scalar_t__ _funcptr_glUniform4uivEXT ; 

__attribute__((used)) static int LoadExt_EXT_gpu_shader4()
{
	int numFailed = 0;
	_funcptr_glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC)IntGetProcAddress("glBindFragDataLocationEXT");
	if(!_funcptr_glBindFragDataLocationEXT) ++numFailed;
	_funcptr_glGetFragDataLocationEXT = (PFNGLGETFRAGDATALOCATIONEXTPROC)IntGetProcAddress("glGetFragDataLocationEXT");
	if(!_funcptr_glGetFragDataLocationEXT) ++numFailed;
	_funcptr_glGetUniformuivEXT = (PFNGLGETUNIFORMUIVEXTPROC)IntGetProcAddress("glGetUniformuivEXT");
	if(!_funcptr_glGetUniformuivEXT) ++numFailed;
	_funcptr_glUniform1uiEXT = (PFNGLUNIFORM1UIEXTPROC)IntGetProcAddress("glUniform1uiEXT");
	if(!_funcptr_glUniform1uiEXT) ++numFailed;
	_funcptr_glUniform1uivEXT = (PFNGLUNIFORM1UIVEXTPROC)IntGetProcAddress("glUniform1uivEXT");
	if(!_funcptr_glUniform1uivEXT) ++numFailed;
	_funcptr_glUniform2uiEXT = (PFNGLUNIFORM2UIEXTPROC)IntGetProcAddress("glUniform2uiEXT");
	if(!_funcptr_glUniform2uiEXT) ++numFailed;
	_funcptr_glUniform2uivEXT = (PFNGLUNIFORM2UIVEXTPROC)IntGetProcAddress("glUniform2uivEXT");
	if(!_funcptr_glUniform2uivEXT) ++numFailed;
	_funcptr_glUniform3uiEXT = (PFNGLUNIFORM3UIEXTPROC)IntGetProcAddress("glUniform3uiEXT");
	if(!_funcptr_glUniform3uiEXT) ++numFailed;
	_funcptr_glUniform3uivEXT = (PFNGLUNIFORM3UIVEXTPROC)IntGetProcAddress("glUniform3uivEXT");
	if(!_funcptr_glUniform3uivEXT) ++numFailed;
	_funcptr_glUniform4uiEXT = (PFNGLUNIFORM4UIEXTPROC)IntGetProcAddress("glUniform4uiEXT");
	if(!_funcptr_glUniform4uiEXT) ++numFailed;
	_funcptr_glUniform4uivEXT = (PFNGLUNIFORM4UIVEXTPROC)IntGetProcAddress("glUniform4uivEXT");
	if(!_funcptr_glUniform4uivEXT) ++numFailed;
	return numFailed;
}