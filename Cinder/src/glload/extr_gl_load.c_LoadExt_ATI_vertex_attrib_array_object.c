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
typedef  scalar_t__ PFNGLVERTEXATTRIBARRAYOBJECTATIPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetVertexAttribArrayObjectfvATI ; 
 scalar_t__ _funcptr_glGetVertexAttribArrayObjectivATI ; 
 scalar_t__ _funcptr_glVertexAttribArrayObjectATI ; 

__attribute__((used)) static int LoadExt_ATI_vertex_attrib_array_object()
{
	int numFailed = 0;
	_funcptr_glGetVertexAttribArrayObjectfvATI = (PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)IntGetProcAddress("glGetVertexAttribArrayObjectfvATI");
	if(!_funcptr_glGetVertexAttribArrayObjectfvATI) ++numFailed;
	_funcptr_glGetVertexAttribArrayObjectivATI = (PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)IntGetProcAddress("glGetVertexAttribArrayObjectivATI");
	if(!_funcptr_glGetVertexAttribArrayObjectivATI) ++numFailed;
	_funcptr_glVertexAttribArrayObjectATI = (PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)IntGetProcAddress("glVertexAttribArrayObjectATI");
	if(!_funcptr_glVertexAttribArrayObjectATI) ++numFailed;
	return numFailed;
}