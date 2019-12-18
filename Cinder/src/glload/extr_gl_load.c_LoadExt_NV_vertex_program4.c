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
typedef  scalar_t__ PFNGLVERTEXATTRIBIPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4USVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UBVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4SVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4BVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1IEXTPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBIUIVEXTPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBIIVEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetVertexAttribIivEXT ; 
 scalar_t__ _funcptr_glGetVertexAttribIuivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI1iEXT ; 
 scalar_t__ _funcptr_glVertexAttribI1ivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI1uiEXT ; 
 scalar_t__ _funcptr_glVertexAttribI1uivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI2iEXT ; 
 scalar_t__ _funcptr_glVertexAttribI2ivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI2uiEXT ; 
 scalar_t__ _funcptr_glVertexAttribI2uivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI3iEXT ; 
 scalar_t__ _funcptr_glVertexAttribI3ivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI3uiEXT ; 
 scalar_t__ _funcptr_glVertexAttribI3uivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4bvEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4iEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4ivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4svEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4ubvEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4uiEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4uivEXT ; 
 scalar_t__ _funcptr_glVertexAttribI4usvEXT ; 
 scalar_t__ _funcptr_glVertexAttribIPointerEXT ; 

__attribute__((used)) static int LoadExt_NV_vertex_program4()
{
	int numFailed = 0;
	_funcptr_glGetVertexAttribIivEXT = (PFNGLGETVERTEXATTRIBIIVEXTPROC)IntGetProcAddress("glGetVertexAttribIivEXT");
	if(!_funcptr_glGetVertexAttribIivEXT) ++numFailed;
	_funcptr_glGetVertexAttribIuivEXT = (PFNGLGETVERTEXATTRIBIUIVEXTPROC)IntGetProcAddress("glGetVertexAttribIuivEXT");
	if(!_funcptr_glGetVertexAttribIuivEXT) ++numFailed;
	_funcptr_glVertexAttribI1iEXT = (PFNGLVERTEXATTRIBI1IEXTPROC)IntGetProcAddress("glVertexAttribI1iEXT");
	if(!_funcptr_glVertexAttribI1iEXT) ++numFailed;
	_funcptr_glVertexAttribI1ivEXT = (PFNGLVERTEXATTRIBI1IVEXTPROC)IntGetProcAddress("glVertexAttribI1ivEXT");
	if(!_funcptr_glVertexAttribI1ivEXT) ++numFailed;
	_funcptr_glVertexAttribI1uiEXT = (PFNGLVERTEXATTRIBI1UIEXTPROC)IntGetProcAddress("glVertexAttribI1uiEXT");
	if(!_funcptr_glVertexAttribI1uiEXT) ++numFailed;
	_funcptr_glVertexAttribI1uivEXT = (PFNGLVERTEXATTRIBI1UIVEXTPROC)IntGetProcAddress("glVertexAttribI1uivEXT");
	if(!_funcptr_glVertexAttribI1uivEXT) ++numFailed;
	_funcptr_glVertexAttribI2iEXT = (PFNGLVERTEXATTRIBI2IEXTPROC)IntGetProcAddress("glVertexAttribI2iEXT");
	if(!_funcptr_glVertexAttribI2iEXT) ++numFailed;
	_funcptr_glVertexAttribI2ivEXT = (PFNGLVERTEXATTRIBI2IVEXTPROC)IntGetProcAddress("glVertexAttribI2ivEXT");
	if(!_funcptr_glVertexAttribI2ivEXT) ++numFailed;
	_funcptr_glVertexAttribI2uiEXT = (PFNGLVERTEXATTRIBI2UIEXTPROC)IntGetProcAddress("glVertexAttribI2uiEXT");
	if(!_funcptr_glVertexAttribI2uiEXT) ++numFailed;
	_funcptr_glVertexAttribI2uivEXT = (PFNGLVERTEXATTRIBI2UIVEXTPROC)IntGetProcAddress("glVertexAttribI2uivEXT");
	if(!_funcptr_glVertexAttribI2uivEXT) ++numFailed;
	_funcptr_glVertexAttribI3iEXT = (PFNGLVERTEXATTRIBI3IEXTPROC)IntGetProcAddress("glVertexAttribI3iEXT");
	if(!_funcptr_glVertexAttribI3iEXT) ++numFailed;
	_funcptr_glVertexAttribI3ivEXT = (PFNGLVERTEXATTRIBI3IVEXTPROC)IntGetProcAddress("glVertexAttribI3ivEXT");
	if(!_funcptr_glVertexAttribI3ivEXT) ++numFailed;
	_funcptr_glVertexAttribI3uiEXT = (PFNGLVERTEXATTRIBI3UIEXTPROC)IntGetProcAddress("glVertexAttribI3uiEXT");
	if(!_funcptr_glVertexAttribI3uiEXT) ++numFailed;
	_funcptr_glVertexAttribI3uivEXT = (PFNGLVERTEXATTRIBI3UIVEXTPROC)IntGetProcAddress("glVertexAttribI3uivEXT");
	if(!_funcptr_glVertexAttribI3uivEXT) ++numFailed;
	_funcptr_glVertexAttribI4bvEXT = (PFNGLVERTEXATTRIBI4BVEXTPROC)IntGetProcAddress("glVertexAttribI4bvEXT");
	if(!_funcptr_glVertexAttribI4bvEXT) ++numFailed;
	_funcptr_glVertexAttribI4iEXT = (PFNGLVERTEXATTRIBI4IEXTPROC)IntGetProcAddress("glVertexAttribI4iEXT");
	if(!_funcptr_glVertexAttribI4iEXT) ++numFailed;
	_funcptr_glVertexAttribI4ivEXT = (PFNGLVERTEXATTRIBI4IVEXTPROC)IntGetProcAddress("glVertexAttribI4ivEXT");
	if(!_funcptr_glVertexAttribI4ivEXT) ++numFailed;
	_funcptr_glVertexAttribI4svEXT = (PFNGLVERTEXATTRIBI4SVEXTPROC)IntGetProcAddress("glVertexAttribI4svEXT");
	if(!_funcptr_glVertexAttribI4svEXT) ++numFailed;
	_funcptr_glVertexAttribI4ubvEXT = (PFNGLVERTEXATTRIBI4UBVEXTPROC)IntGetProcAddress("glVertexAttribI4ubvEXT");
	if(!_funcptr_glVertexAttribI4ubvEXT) ++numFailed;
	_funcptr_glVertexAttribI4uiEXT = (PFNGLVERTEXATTRIBI4UIEXTPROC)IntGetProcAddress("glVertexAttribI4uiEXT");
	if(!_funcptr_glVertexAttribI4uiEXT) ++numFailed;
	_funcptr_glVertexAttribI4uivEXT = (PFNGLVERTEXATTRIBI4UIVEXTPROC)IntGetProcAddress("glVertexAttribI4uivEXT");
	if(!_funcptr_glVertexAttribI4uivEXT) ++numFailed;
	_funcptr_glVertexAttribI4usvEXT = (PFNGLVERTEXATTRIBI4USVEXTPROC)IntGetProcAddress("glVertexAttribI4usvEXT");
	if(!_funcptr_glVertexAttribI4usvEXT) ++numFailed;
	_funcptr_glVertexAttribIPointerEXT = (PFNGLVERTEXATTRIBIPOINTEREXTPROC)IntGetProcAddress("glVertexAttribIPointerEXT");
	if(!_funcptr_glVertexAttribIPointerEXT) ++numFailed;
	return numFailed;
}