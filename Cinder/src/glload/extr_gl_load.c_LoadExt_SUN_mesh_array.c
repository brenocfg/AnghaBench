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
typedef  scalar_t__ PFNGLDRAWMESHARRAYSSUNPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDrawMeshArraysSUN ; 

__attribute__((used)) static int LoadExt_SUN_mesh_array()
{
	int numFailed = 0;
	_funcptr_glDrawMeshArraysSUN = (PFNGLDRAWMESHARRAYSSUNPROC)IntGetProcAddress("glDrawMeshArraysSUN");
	if(!_funcptr_glDrawMeshArraysSUN) ++numFailed;
	return numFailed;
}