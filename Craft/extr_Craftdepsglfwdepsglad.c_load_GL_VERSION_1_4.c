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
typedef  scalar_t__ PFNGLPOINTPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERIPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSPROC ;
typedef  scalar_t__ PFNGLBLENDFUNCSEPARATEPROC ;
typedef  scalar_t__ PFNGLBLENDEQUATIONPROC ;
typedef  scalar_t__ PFNGLBLENDCOLORPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_4 ; 
 scalar_t__ glad_glBlendColor ; 
 scalar_t__ glad_glBlendEquation ; 
 scalar_t__ glad_glBlendFuncSeparate ; 
 scalar_t__ glad_glMultiDrawArrays ; 
 scalar_t__ glad_glMultiDrawElements ; 
 scalar_t__ glad_glPointParameterf ; 
 scalar_t__ glad_glPointParameterfv ; 
 scalar_t__ glad_glPointParameteri ; 
 scalar_t__ glad_glPointParameteriv ; 

__attribute__((used)) static void load_GL_VERSION_1_4(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_4) return;
	glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)load("glBlendFuncSeparate");
	glad_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)load("glMultiDrawArrays");
	glad_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)load("glMultiDrawElements");
	glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)load("glPointParameterf");
	glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)load("glPointParameterfv");
	glad_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)load("glPointParameteri");
	glad_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)load("glPointParameteriv");
	glad_glBlendColor = (PFNGLBLENDCOLORPROC)load("glBlendColor");
	glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)load("glBlendEquation");
}