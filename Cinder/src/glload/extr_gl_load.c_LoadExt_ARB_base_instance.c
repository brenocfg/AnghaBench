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
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDrawArraysInstancedBaseInstance ; 
 scalar_t__ _funcptr_glDrawElementsInstancedBaseInstance ; 
 scalar_t__ _funcptr_glDrawElementsInstancedBaseVertexBaseInstance ; 

__attribute__((used)) static int LoadExt_ARB_base_instance()
{
	int numFailed = 0;
	_funcptr_glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawArraysInstancedBaseInstance");
	if(!_funcptr_glDrawArraysInstancedBaseInstance) ++numFailed;
	_funcptr_glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseInstance");
	if(!_funcptr_glDrawElementsInstancedBaseInstance) ++numFailed;
	_funcptr_glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
	if(!_funcptr_glDrawElementsInstancedBaseVertexBaseInstance) ++numFailed;
	return numFailed;
}