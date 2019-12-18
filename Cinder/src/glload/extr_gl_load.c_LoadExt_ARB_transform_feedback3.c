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
typedef  scalar_t__ PFNGLGETQUERYINDEXEDIVPROC ;
typedef  scalar_t__ PFNGLENDQUERYINDEXEDPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYINDEXEDPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginQueryIndexed ; 
 scalar_t__ _funcptr_glDrawTransformFeedbackStream ; 
 scalar_t__ _funcptr_glEndQueryIndexed ; 
 scalar_t__ _funcptr_glGetQueryIndexediv ; 

__attribute__((used)) static int LoadExt_ARB_transform_feedback3()
{
	int numFailed = 0;
	_funcptr_glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)IntGetProcAddress("glBeginQueryIndexed");
	if(!_funcptr_glBeginQueryIndexed) ++numFailed;
	_funcptr_glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)IntGetProcAddress("glDrawTransformFeedbackStream");
	if(!_funcptr_glDrawTransformFeedbackStream) ++numFailed;
	_funcptr_glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)IntGetProcAddress("glEndQueryIndexed");
	if(!_funcptr_glEndQueryIndexed) ++numFailed;
	_funcptr_glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)IntGetProcAddress("glGetQueryIndexediv");
	if(!_funcptr_glGetQueryIndexediv) ++numFailed;
	return numFailed;
}