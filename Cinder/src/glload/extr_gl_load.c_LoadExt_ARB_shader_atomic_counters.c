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
typedef  scalar_t__ PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetActiveAtomicCounterBufferiv ; 

__attribute__((used)) static int LoadExt_ARB_shader_atomic_counters()
{
	int numFailed = 0;
	_funcptr_glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)IntGetProcAddress("glGetActiveAtomicCounterBufferiv");
	if(!_funcptr_glGetActiveAtomicCounterBufferiv) ++numFailed;
	return numFailed;
}