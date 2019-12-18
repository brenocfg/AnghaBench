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
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDrawTransformFeedbackInstanced ; 
 scalar_t__ _funcptr_glDrawTransformFeedbackStreamInstanced ; 

__attribute__((used)) static int LoadExt_ARB_transform_feedback_instanced()
{
	int numFailed = 0;
	_funcptr_glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackInstanced");
	if(!_funcptr_glDrawTransformFeedbackInstanced) ++numFailed;
	_funcptr_glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackStreamInstanced");
	if(!_funcptr_glDrawTransformFeedbackStreamInstanced) ++numFailed;
	return numFailed;
}