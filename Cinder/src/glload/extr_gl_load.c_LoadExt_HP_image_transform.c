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
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERIVHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERIHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERFVHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERFHPPROC ;
typedef  scalar_t__ PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC ;
typedef  scalar_t__ PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetImageTransformParameterfvHP ; 
 scalar_t__ _funcptr_glGetImageTransformParameterivHP ; 
 scalar_t__ _funcptr_glImageTransformParameterfHP ; 
 scalar_t__ _funcptr_glImageTransformParameterfvHP ; 
 scalar_t__ _funcptr_glImageTransformParameteriHP ; 
 scalar_t__ _funcptr_glImageTransformParameterivHP ; 

__attribute__((used)) static int LoadExt_HP_image_transform()
{
	int numFailed = 0;
	_funcptr_glGetImageTransformParameterfvHP = (PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)IntGetProcAddress("glGetImageTransformParameterfvHP");
	if(!_funcptr_glGetImageTransformParameterfvHP) ++numFailed;
	_funcptr_glGetImageTransformParameterivHP = (PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)IntGetProcAddress("glGetImageTransformParameterivHP");
	if(!_funcptr_glGetImageTransformParameterivHP) ++numFailed;
	_funcptr_glImageTransformParameterfHP = (PFNGLIMAGETRANSFORMPARAMETERFHPPROC)IntGetProcAddress("glImageTransformParameterfHP");
	if(!_funcptr_glImageTransformParameterfHP) ++numFailed;
	_funcptr_glImageTransformParameterfvHP = (PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)IntGetProcAddress("glImageTransformParameterfvHP");
	if(!_funcptr_glImageTransformParameterfvHP) ++numFailed;
	_funcptr_glImageTransformParameteriHP = (PFNGLIMAGETRANSFORMPARAMETERIHPPROC)IntGetProcAddress("glImageTransformParameteriHP");
	if(!_funcptr_glImageTransformParameteriHP) ++numFailed;
	_funcptr_glImageTransformParameterivHP = (PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)IntGetProcAddress("glImageTransformParameterivHP");
	if(!_funcptr_glImageTransformParameterivHP) ++numFailed;
	return numFailed;
}