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
typedef  scalar_t__ PFNGLGETDEBUGMESSAGELOGARBPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGEINSERTARBPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECONTROLARBPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECALLBACKARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDebugMessageCallbackARB ; 
 scalar_t__ _funcptr_glDebugMessageControlARB ; 
 scalar_t__ _funcptr_glDebugMessageInsertARB ; 
 scalar_t__ _funcptr_glGetDebugMessageLogARB ; 

__attribute__((used)) static int LoadExt_ARB_debug_output()
{
	int numFailed = 0;
	_funcptr_glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)IntGetProcAddress("glDebugMessageCallbackARB");
	if(!_funcptr_glDebugMessageCallbackARB) ++numFailed;
	_funcptr_glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)IntGetProcAddress("glDebugMessageControlARB");
	if(!_funcptr_glDebugMessageControlARB) ++numFailed;
	_funcptr_glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)IntGetProcAddress("glDebugMessageInsertARB");
	if(!_funcptr_glDebugMessageInsertARB) ++numFailed;
	_funcptr_glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC)IntGetProcAddress("glGetDebugMessageLogARB");
	if(!_funcptr_glGetDebugMessageLogARB) ++numFailed;
	return numFailed;
}