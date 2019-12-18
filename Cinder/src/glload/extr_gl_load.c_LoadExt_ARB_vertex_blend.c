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
typedef  scalar_t__ PFNGLWEIGHTUSVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTUIVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTUBVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTSVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTPOINTERARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTIVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTFVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTDVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTBVARBPROC ;
typedef  scalar_t__ PFNGLVERTEXBLENDARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glVertexBlendARB ; 
 scalar_t__ _funcptr_glWeightPointerARB ; 
 scalar_t__ _funcptr_glWeightbvARB ; 
 scalar_t__ _funcptr_glWeightdvARB ; 
 scalar_t__ _funcptr_glWeightfvARB ; 
 scalar_t__ _funcptr_glWeightivARB ; 
 scalar_t__ _funcptr_glWeightsvARB ; 
 scalar_t__ _funcptr_glWeightubvARB ; 
 scalar_t__ _funcptr_glWeightuivARB ; 
 scalar_t__ _funcptr_glWeightusvARB ; 

__attribute__((used)) static int LoadExt_ARB_vertex_blend()
{
	int numFailed = 0;
	_funcptr_glVertexBlendARB = (PFNGLVERTEXBLENDARBPROC)IntGetProcAddress("glVertexBlendARB");
	if(!_funcptr_glVertexBlendARB) ++numFailed;
	_funcptr_glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC)IntGetProcAddress("glWeightPointerARB");
	if(!_funcptr_glWeightPointerARB) ++numFailed;
	_funcptr_glWeightbvARB = (PFNGLWEIGHTBVARBPROC)IntGetProcAddress("glWeightbvARB");
	if(!_funcptr_glWeightbvARB) ++numFailed;
	_funcptr_glWeightdvARB = (PFNGLWEIGHTDVARBPROC)IntGetProcAddress("glWeightdvARB");
	if(!_funcptr_glWeightdvARB) ++numFailed;
	_funcptr_glWeightfvARB = (PFNGLWEIGHTFVARBPROC)IntGetProcAddress("glWeightfvARB");
	if(!_funcptr_glWeightfvARB) ++numFailed;
	_funcptr_glWeightivARB = (PFNGLWEIGHTIVARBPROC)IntGetProcAddress("glWeightivARB");
	if(!_funcptr_glWeightivARB) ++numFailed;
	_funcptr_glWeightsvARB = (PFNGLWEIGHTSVARBPROC)IntGetProcAddress("glWeightsvARB");
	if(!_funcptr_glWeightsvARB) ++numFailed;
	_funcptr_glWeightubvARB = (PFNGLWEIGHTUBVARBPROC)IntGetProcAddress("glWeightubvARB");
	if(!_funcptr_glWeightubvARB) ++numFailed;
	_funcptr_glWeightuivARB = (PFNGLWEIGHTUIVARBPROC)IntGetProcAddress("glWeightuivARB");
	if(!_funcptr_glWeightuivARB) ++numFailed;
	_funcptr_glWeightusvARB = (PFNGLWEIGHTUSVARBPROC)IntGetProcAddress("glWeightusvARB");
	if(!_funcptr_glWeightusvARB) ++numFailed;
	return numFailed;
}