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
typedef  scalar_t__ PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLELEMENTPOINTERAPPLEPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTARRAYAPPLEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDrawElementArrayAPPLE ; 
 scalar_t__ _funcptr_glDrawRangeElementArrayAPPLE ; 
 scalar_t__ _funcptr_glElementPointerAPPLE ; 
 scalar_t__ _funcptr_glMultiDrawElementArrayAPPLE ; 
 scalar_t__ _funcptr_glMultiDrawRangeElementArrayAPPLE ; 

__attribute__((used)) static int LoadExt_APPLE_element_array()
{
	int numFailed = 0;
	_funcptr_glDrawElementArrayAPPLE = (PFNGLDRAWELEMENTARRAYAPPLEPROC)IntGetProcAddress("glDrawElementArrayAPPLE");
	if(!_funcptr_glDrawElementArrayAPPLE) ++numFailed;
	_funcptr_glDrawRangeElementArrayAPPLE = (PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)IntGetProcAddress("glDrawRangeElementArrayAPPLE");
	if(!_funcptr_glDrawRangeElementArrayAPPLE) ++numFailed;
	_funcptr_glElementPointerAPPLE = (PFNGLELEMENTPOINTERAPPLEPROC)IntGetProcAddress("glElementPointerAPPLE");
	if(!_funcptr_glElementPointerAPPLE) ++numFailed;
	_funcptr_glMultiDrawElementArrayAPPLE = (PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)IntGetProcAddress("glMultiDrawElementArrayAPPLE");
	if(!_funcptr_glMultiDrawElementArrayAPPLE) ++numFailed;
	_funcptr_glMultiDrawRangeElementArrayAPPLE = (PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)IntGetProcAddress("glMultiDrawRangeElementArrayAPPLE");
	if(!_funcptr_glMultiDrawRangeElementArrayAPPLE) ++numFailed;
	return numFailed;
}