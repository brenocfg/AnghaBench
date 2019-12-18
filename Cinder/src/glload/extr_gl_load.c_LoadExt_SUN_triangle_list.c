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
typedef  scalar_t__ PFNGLREPLACEMENTCODEUSVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUSSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUIVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUISUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUBVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUBSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEPOINTERSUNPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glReplacementCodePointerSUN ; 
 scalar_t__ _funcptr_glReplacementCodeubSUN ; 
 scalar_t__ _funcptr_glReplacementCodeubvSUN ; 
 scalar_t__ _funcptr_glReplacementCodeuiSUN ; 
 scalar_t__ _funcptr_glReplacementCodeuivSUN ; 
 scalar_t__ _funcptr_glReplacementCodeusSUN ; 
 scalar_t__ _funcptr_glReplacementCodeusvSUN ; 

__attribute__((used)) static int LoadExt_SUN_triangle_list()
{
	int numFailed = 0;
	_funcptr_glReplacementCodePointerSUN = (PFNGLREPLACEMENTCODEPOINTERSUNPROC)IntGetProcAddress("glReplacementCodePointerSUN");
	if(!_funcptr_glReplacementCodePointerSUN) ++numFailed;
	_funcptr_glReplacementCodeubSUN = (PFNGLREPLACEMENTCODEUBSUNPROC)IntGetProcAddress("glReplacementCodeubSUN");
	if(!_funcptr_glReplacementCodeubSUN) ++numFailed;
	_funcptr_glReplacementCodeubvSUN = (PFNGLREPLACEMENTCODEUBVSUNPROC)IntGetProcAddress("glReplacementCodeubvSUN");
	if(!_funcptr_glReplacementCodeubvSUN) ++numFailed;
	_funcptr_glReplacementCodeuiSUN = (PFNGLREPLACEMENTCODEUISUNPROC)IntGetProcAddress("glReplacementCodeuiSUN");
	if(!_funcptr_glReplacementCodeuiSUN) ++numFailed;
	_funcptr_glReplacementCodeuivSUN = (PFNGLREPLACEMENTCODEUIVSUNPROC)IntGetProcAddress("glReplacementCodeuivSUN");
	if(!_funcptr_glReplacementCodeuivSUN) ++numFailed;
	_funcptr_glReplacementCodeusSUN = (PFNGLREPLACEMENTCODEUSSUNPROC)IntGetProcAddress("glReplacementCodeusSUN");
	if(!_funcptr_glReplacementCodeusSUN) ++numFailed;
	_funcptr_glReplacementCodeusvSUN = (PFNGLREPLACEMENTCODEUSVSUNPROC)IntGetProcAddress("glReplacementCodeusvSUN");
	if(!_funcptr_glReplacementCodeusvSUN) ++numFailed;
	return numFailed;
}