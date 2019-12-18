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
typedef  scalar_t__ PFNGLRESUMETRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLPAUSETRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLISTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLGENTRANSFORMFEEDBACKSNVPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLDELETETRANSFORMFEEDBACKSNVPROC ;
typedef  scalar_t__ PFNGLBINDTRANSFORMFEEDBACKNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindTransformFeedbackNV ; 
 scalar_t__ _funcptr_glDeleteTransformFeedbacksNV ; 
 scalar_t__ _funcptr_glDrawTransformFeedbackNV ; 
 scalar_t__ _funcptr_glGenTransformFeedbacksNV ; 
 scalar_t__ _funcptr_glIsTransformFeedbackNV ; 
 scalar_t__ _funcptr_glPauseTransformFeedbackNV ; 
 scalar_t__ _funcptr_glResumeTransformFeedbackNV ; 

__attribute__((used)) static int LoadExt_NV_transform_feedback2()
{
	int numFailed = 0;
	_funcptr_glBindTransformFeedbackNV = (PFNGLBINDTRANSFORMFEEDBACKNVPROC)IntGetProcAddress("glBindTransformFeedbackNV");
	if(!_funcptr_glBindTransformFeedbackNV) ++numFailed;
	_funcptr_glDeleteTransformFeedbacksNV = (PFNGLDELETETRANSFORMFEEDBACKSNVPROC)IntGetProcAddress("glDeleteTransformFeedbacksNV");
	if(!_funcptr_glDeleteTransformFeedbacksNV) ++numFailed;
	_funcptr_glDrawTransformFeedbackNV = (PFNGLDRAWTRANSFORMFEEDBACKNVPROC)IntGetProcAddress("glDrawTransformFeedbackNV");
	if(!_funcptr_glDrawTransformFeedbackNV) ++numFailed;
	_funcptr_glGenTransformFeedbacksNV = (PFNGLGENTRANSFORMFEEDBACKSNVPROC)IntGetProcAddress("glGenTransformFeedbacksNV");
	if(!_funcptr_glGenTransformFeedbacksNV) ++numFailed;
	_funcptr_glIsTransformFeedbackNV = (PFNGLISTRANSFORMFEEDBACKNVPROC)IntGetProcAddress("glIsTransformFeedbackNV");
	if(!_funcptr_glIsTransformFeedbackNV) ++numFailed;
	_funcptr_glPauseTransformFeedbackNV = (PFNGLPAUSETRANSFORMFEEDBACKNVPROC)IntGetProcAddress("glPauseTransformFeedbackNV");
	if(!_funcptr_glPauseTransformFeedbackNV) ++numFailed;
	_funcptr_glResumeTransformFeedbackNV = (PFNGLRESUMETRANSFORMFEEDBACKNVPROC)IntGetProcAddress("glResumeTransformFeedbackNV");
	if(!_funcptr_glResumeTransformFeedbackNV) ++numFailed;
	return numFailed;
}