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
typedef  scalar_t__ PFNGLVERTEXPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERVINTELPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glColorPointervINTEL ; 
 scalar_t__ _funcptr_glNormalPointervINTEL ; 
 scalar_t__ _funcptr_glTexCoordPointervINTEL ; 
 scalar_t__ _funcptr_glVertexPointervINTEL ; 

__attribute__((used)) static int LoadExt_INTEL_parallel_arrays()
{
	int numFailed = 0;
	_funcptr_glColorPointervINTEL = (PFNGLCOLORPOINTERVINTELPROC)IntGetProcAddress("glColorPointervINTEL");
	if(!_funcptr_glColorPointervINTEL) ++numFailed;
	_funcptr_glNormalPointervINTEL = (PFNGLNORMALPOINTERVINTELPROC)IntGetProcAddress("glNormalPointervINTEL");
	if(!_funcptr_glNormalPointervINTEL) ++numFailed;
	_funcptr_glTexCoordPointervINTEL = (PFNGLTEXCOORDPOINTERVINTELPROC)IntGetProcAddress("glTexCoordPointervINTEL");
	if(!_funcptr_glTexCoordPointervINTEL) ++numFailed;
	_funcptr_glVertexPointervINTEL = (PFNGLVERTEXPOINTERVINTELPROC)IntGetProcAddress("glVertexPointervINTEL");
	if(!_funcptr_glVertexPointervINTEL) ++numFailed;
	return numFailed;
}