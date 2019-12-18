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
typedef  scalar_t__ PFNGLRESUMETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLPAUSETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLISTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLGENTRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLDELETETRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLBINDTRANSFORMFEEDBACKPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindTransformFeedback ; 
 scalar_t__ _funcptr_glDeleteTransformFeedbacks ; 
 scalar_t__ _funcptr_glDrawTransformFeedback ; 
 scalar_t__ _funcptr_glGenTransformFeedbacks ; 
 scalar_t__ _funcptr_glIsTransformFeedback ; 
 scalar_t__ _funcptr_glPauseTransformFeedback ; 
 scalar_t__ _funcptr_glResumeTransformFeedback ; 

__attribute__((used)) static int LoadExt_ARB_transform_feedback2()
{
	int numFailed = 0;
	_funcptr_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBindTransformFeedback");
	if(!_funcptr_glBindTransformFeedback) ++numFailed;
	_funcptr_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)IntGetProcAddress("glDeleteTransformFeedbacks");
	if(!_funcptr_glDeleteTransformFeedbacks) ++numFailed;
	_funcptr_glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)IntGetProcAddress("glDrawTransformFeedback");
	if(!_funcptr_glDrawTransformFeedback) ++numFailed;
	_funcptr_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)IntGetProcAddress("glGenTransformFeedbacks");
	if(!_funcptr_glGenTransformFeedbacks) ++numFailed;
	_funcptr_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)IntGetProcAddress("glIsTransformFeedback");
	if(!_funcptr_glIsTransformFeedback) ++numFailed;
	_funcptr_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)IntGetProcAddress("glPauseTransformFeedback");
	if(!_funcptr_glPauseTransformFeedback) ++numFailed;
	_funcptr_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)IntGetProcAddress("glResumeTransformFeedback");
	if(!_funcptr_glResumeTransformFeedback) ++numFailed;
	return numFailed;
}