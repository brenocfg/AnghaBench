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
typedef  scalar_t__ PFNGLPUSHDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLPOPDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLGETOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLGETDEBUGMESSAGELOGPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGEINSERTPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECONTROLPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECALLBACKPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDebugMessageCallback ; 
 scalar_t__ _funcptr_glDebugMessageControl ; 
 scalar_t__ _funcptr_glDebugMessageInsert ; 
 scalar_t__ _funcptr_glGetDebugMessageLog ; 
 scalar_t__ _funcptr_glGetObjectLabel ; 
 scalar_t__ _funcptr_glGetObjectPtrLabel ; 
 scalar_t__ _funcptr_glGetPointerv ; 
 scalar_t__ _funcptr_glObjectLabel ; 
 scalar_t__ _funcptr_glObjectPtrLabel ; 
 scalar_t__ _funcptr_glPopDebugGroup ; 
 scalar_t__ _funcptr_glPushDebugGroup ; 

__attribute__((used)) static int LoadExt_KHR_debug()
{
	int numFailed = 0;
	_funcptr_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)IntGetProcAddress("glDebugMessageCallback");
	if(!_funcptr_glDebugMessageCallback) ++numFailed;
	_funcptr_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)IntGetProcAddress("glDebugMessageControl");
	if(!_funcptr_glDebugMessageControl) ++numFailed;
	_funcptr_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)IntGetProcAddress("glDebugMessageInsert");
	if(!_funcptr_glDebugMessageInsert) ++numFailed;
	_funcptr_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)IntGetProcAddress("glGetDebugMessageLog");
	if(!_funcptr_glGetDebugMessageLog) ++numFailed;
	_funcptr_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)IntGetProcAddress("glGetObjectLabel");
	if(!_funcptr_glGetObjectLabel) ++numFailed;
	_funcptr_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)IntGetProcAddress("glGetObjectPtrLabel");
	if(!_funcptr_glGetObjectPtrLabel) ++numFailed;
	_funcptr_glGetPointerv = (PFNGLGETPOINTERVPROC)IntGetProcAddress("glGetPointerv");
	if(!_funcptr_glGetPointerv) ++numFailed;
	_funcptr_glObjectLabel = (PFNGLOBJECTLABELPROC)IntGetProcAddress("glObjectLabel");
	if(!_funcptr_glObjectLabel) ++numFailed;
	_funcptr_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)IntGetProcAddress("glObjectPtrLabel");
	if(!_funcptr_glObjectPtrLabel) ++numFailed;
	_funcptr_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)IntGetProcAddress("glPopDebugGroup");
	if(!_funcptr_glPopDebugGroup) ++numFailed;
	_funcptr_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)IntGetProcAddress("glPushDebugGroup");
	if(!_funcptr_glPushDebugGroup) ++numFailed;
	return numFailed;
}