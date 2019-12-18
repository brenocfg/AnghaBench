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

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glClientWaitSync ; 
 scalar_t__ _funcptr_glDeleteSync ; 
 scalar_t__ _funcptr_glDrawElementsBaseVertex ; 
 scalar_t__ _funcptr_glDrawElementsInstancedBaseVertex ; 
 scalar_t__ _funcptr_glDrawRangeElementsBaseVertex ; 
 scalar_t__ _funcptr_glFenceSync ; 
 scalar_t__ _funcptr_glFramebufferTexture ; 
 scalar_t__ _funcptr_glGetBufferParameteri64v ; 
 scalar_t__ _funcptr_glGetInteger64i_v ; 
 scalar_t__ _funcptr_glGetInteger64v ; 
 scalar_t__ _funcptr_glGetMultisamplefv ; 
 scalar_t__ _funcptr_glGetSynciv ; 
 scalar_t__ _funcptr_glIsSync ; 
 scalar_t__ _funcptr_glMultiDrawElementsBaseVertex ; 
 scalar_t__ _funcptr_glProvokingVertex ; 
 scalar_t__ _funcptr_glSampleMaski ; 
 scalar_t__ _funcptr_glTexImage2DMultisample ; 
 scalar_t__ _funcptr_glTexImage3DMultisample ; 
 scalar_t__ _funcptr_glWaitSync ; 

__attribute__((used)) static int LoadCore_Version_3_2()
{
	int numFailed = 0;
	_funcptr_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)IntGetProcAddress("glClientWaitSync");
	if(!_funcptr_glClientWaitSync) ++numFailed;
	_funcptr_glDeleteSync = (PFNGLDELETESYNCPROC)IntGetProcAddress("glDeleteSync");
	if(!_funcptr_glDeleteSync) ++numFailed;
	_funcptr_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawElementsBaseVertex");
	if(!_funcptr_glDrawElementsBaseVertex) ++numFailed;
	_funcptr_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertex");
	if(!_funcptr_glDrawElementsInstancedBaseVertex) ++numFailed;
	_funcptr_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawRangeElementsBaseVertex");
	if(!_funcptr_glDrawRangeElementsBaseVertex) ++numFailed;
	_funcptr_glFenceSync = (PFNGLFENCESYNCPROC)IntGetProcAddress("glFenceSync");
	if(!_funcptr_glFenceSync) ++numFailed;
	_funcptr_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glFramebufferTexture");
	if(!_funcptr_glFramebufferTexture) ++numFailed;
	_funcptr_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetBufferParameteri64v");
	if(!_funcptr_glGetBufferParameteri64v) ++numFailed;
	_funcptr_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)IntGetProcAddress("glGetInteger64i_v");
	if(!_funcptr_glGetInteger64i_v) ++numFailed;
	_funcptr_glGetInteger64v = (PFNGLGETINTEGER64VPROC)IntGetProcAddress("glGetInteger64v");
	if(!_funcptr_glGetInteger64v) ++numFailed;
	_funcptr_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)IntGetProcAddress("glGetMultisamplefv");
	if(!_funcptr_glGetMultisamplefv) ++numFailed;
	_funcptr_glGetSynciv = (PFNGLGETSYNCIVPROC)IntGetProcAddress("glGetSynciv");
	if(!_funcptr_glGetSynciv) ++numFailed;
	_funcptr_glIsSync = (PFNGLISSYNCPROC)IntGetProcAddress("glIsSync");
	if(!_funcptr_glIsSync) ++numFailed;
	_funcptr_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glMultiDrawElementsBaseVertex");
	if(!_funcptr_glMultiDrawElementsBaseVertex) ++numFailed;
	_funcptr_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)IntGetProcAddress("glProvokingVertex");
	if(!_funcptr_glProvokingVertex) ++numFailed;
	_funcptr_glSampleMaski = (PFNGLSAMPLEMASKIPROC)IntGetProcAddress("glSampleMaski");
	if(!_funcptr_glSampleMaski) ++numFailed;
	_funcptr_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexImage2DMultisample");
	if(!_funcptr_glTexImage2DMultisample) ++numFailed;
	_funcptr_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexImage3DMultisample");
	if(!_funcptr_glTexImage3DMultisample) ++numFailed;
	_funcptr_glWaitSync = (PFNGLWAITSYNCPROC)IntGetProcAddress("glWaitSync");
	if(!_funcptr_glWaitSync) ++numFailed;
	return numFailed;
}