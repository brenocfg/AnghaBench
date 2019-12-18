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
typedef  scalar_t__ PFNGLWAITSYNCPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE2DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKIPROC ;
typedef  scalar_t__ PFNGLPROVOKINGVERTEXPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLISSYNCPROC ;
typedef  scalar_t__ PFNGLGETSYNCIVPROC ;
typedef  scalar_t__ PFNGLGETMULTISAMPLEFVPROC ;
typedef  scalar_t__ PFNGLGETINTEGER64VPROC ;
typedef  scalar_t__ PFNGLGETINTEGER64I_VPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERI64VPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREPROC ;
typedef  scalar_t__ PFNGLFENCESYNCPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDELETESYNCPROC ;
typedef  scalar_t__ PFNGLCLIENTWAITSYNCPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_3_2 ; 
 scalar_t__ glad_glClientWaitSync ; 
 scalar_t__ glad_glDeleteSync ; 
 scalar_t__ glad_glDrawElementsBaseVertex ; 
 scalar_t__ glad_glDrawElementsInstancedBaseVertex ; 
 scalar_t__ glad_glDrawRangeElementsBaseVertex ; 
 scalar_t__ glad_glFenceSync ; 
 scalar_t__ glad_glFramebufferTexture ; 
 scalar_t__ glad_glGetBufferParameteri64v ; 
 scalar_t__ glad_glGetInteger64i_v ; 
 scalar_t__ glad_glGetInteger64v ; 
 scalar_t__ glad_glGetMultisamplefv ; 
 scalar_t__ glad_glGetSynciv ; 
 scalar_t__ glad_glIsSync ; 
 scalar_t__ glad_glMultiDrawElementsBaseVertex ; 
 scalar_t__ glad_glProvokingVertex ; 
 scalar_t__ glad_glSampleMaski ; 
 scalar_t__ glad_glTexImage2DMultisample ; 
 scalar_t__ glad_glTexImage3DMultisample ; 
 scalar_t__ glad_glWaitSync ; 

__attribute__((used)) static void load_GL_VERSION_3_2(GLADloadproc load) {
	if(!GLAD_GL_VERSION_3_2) return;
	glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)load("glDrawElementsBaseVertex");
	glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)load("glDrawRangeElementsBaseVertex");
	glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)load("glDrawElementsInstancedBaseVertex");
	glad_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)load("glMultiDrawElementsBaseVertex");
	glad_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)load("glProvokingVertex");
	glad_glFenceSync = (PFNGLFENCESYNCPROC)load("glFenceSync");
	glad_glIsSync = (PFNGLISSYNCPROC)load("glIsSync");
	glad_glDeleteSync = (PFNGLDELETESYNCPROC)load("glDeleteSync");
	glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)load("glClientWaitSync");
	glad_glWaitSync = (PFNGLWAITSYNCPROC)load("glWaitSync");
	glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC)load("glGetInteger64v");
	glad_glGetSynciv = (PFNGLGETSYNCIVPROC)load("glGetSynciv");
	glad_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)load("glGetInteger64i_v");
	glad_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)load("glGetBufferParameteri64v");
	glad_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)load("glFramebufferTexture");
	glad_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)load("glTexImage2DMultisample");
	glad_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)load("glTexImage3DMultisample");
	glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)load("glGetMultisamplefv");
	glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC)load("glSampleMaski");
}