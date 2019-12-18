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
typedef  scalar_t__ PFNGLVERTEXATTRIBP4UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP4UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP3UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP3UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP2UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP2UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP1UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP1UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBDIVISORPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIUIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERFPROC ;
typedef  scalar_t__ PFNGLQUERYCOUNTERPROC ;
typedef  scalar_t__ PFNGLISSAMPLERPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIUIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTUI64VPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTI64VPROC ;
typedef  scalar_t__ PFNGLGETFRAGDATAINDEXPROC ;
typedef  scalar_t__ PFNGLGENSAMPLERSPROC ;
typedef  scalar_t__ PFNGLDELETESAMPLERSPROC ;
typedef  scalar_t__ PFNGLBINDSAMPLERPROC ;
typedef  scalar_t__ PFNGLBINDFRAGDATALOCATIONINDEXEDPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindFragDataLocationIndexed ; 
 scalar_t__ _funcptr_glBindSampler ; 
 scalar_t__ _funcptr_glDeleteSamplers ; 
 scalar_t__ _funcptr_glGenSamplers ; 
 scalar_t__ _funcptr_glGetFragDataIndex ; 
 scalar_t__ _funcptr_glGetQueryObjecti64v ; 
 scalar_t__ _funcptr_glGetQueryObjectui64v ; 
 scalar_t__ _funcptr_glGetSamplerParameterIiv ; 
 scalar_t__ _funcptr_glGetSamplerParameterIuiv ; 
 scalar_t__ _funcptr_glGetSamplerParameterfv ; 
 scalar_t__ _funcptr_glGetSamplerParameteriv ; 
 scalar_t__ _funcptr_glIsSampler ; 
 scalar_t__ _funcptr_glQueryCounter ; 
 scalar_t__ _funcptr_glSamplerParameterIiv ; 
 scalar_t__ _funcptr_glSamplerParameterIuiv ; 
 scalar_t__ _funcptr_glSamplerParameterf ; 
 scalar_t__ _funcptr_glSamplerParameterfv ; 
 scalar_t__ _funcptr_glSamplerParameteri ; 
 scalar_t__ _funcptr_glSamplerParameteriv ; 
 scalar_t__ _funcptr_glVertexAttribDivisor ; 
 scalar_t__ _funcptr_glVertexAttribP1ui ; 
 scalar_t__ _funcptr_glVertexAttribP1uiv ; 
 scalar_t__ _funcptr_glVertexAttribP2ui ; 
 scalar_t__ _funcptr_glVertexAttribP2uiv ; 
 scalar_t__ _funcptr_glVertexAttribP3ui ; 
 scalar_t__ _funcptr_glVertexAttribP3uiv ; 
 scalar_t__ _funcptr_glVertexAttribP4ui ; 
 scalar_t__ _funcptr_glVertexAttribP4uiv ; 

__attribute__((used)) static int LoadCore_Version_3_3()
{
	int numFailed = 0;
	_funcptr_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)IntGetProcAddress("glBindFragDataLocationIndexed");
	if(!_funcptr_glBindFragDataLocationIndexed) ++numFailed;
	_funcptr_glBindSampler = (PFNGLBINDSAMPLERPROC)IntGetProcAddress("glBindSampler");
	if(!_funcptr_glBindSampler) ++numFailed;
	_funcptr_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)IntGetProcAddress("glDeleteSamplers");
	if(!_funcptr_glDeleteSamplers) ++numFailed;
	_funcptr_glGenSamplers = (PFNGLGENSAMPLERSPROC)IntGetProcAddress("glGenSamplers");
	if(!_funcptr_glGenSamplers) ++numFailed;
	_funcptr_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)IntGetProcAddress("glGetFragDataIndex");
	if(!_funcptr_glGetFragDataIndex) ++numFailed;
	_funcptr_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)IntGetProcAddress("glGetQueryObjecti64v");
	if(!_funcptr_glGetQueryObjecti64v) ++numFailed;
	_funcptr_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)IntGetProcAddress("glGetQueryObjectui64v");
	if(!_funcptr_glGetQueryObjectui64v) ++numFailed;
	_funcptr_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glGetSamplerParameterIiv");
	if(!_funcptr_glGetSamplerParameterIiv) ++numFailed;
	_funcptr_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glGetSamplerParameterIuiv");
	if(!_funcptr_glGetSamplerParameterIuiv) ++numFailed;
	_funcptr_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)IntGetProcAddress("glGetSamplerParameterfv");
	if(!_funcptr_glGetSamplerParameterfv) ++numFailed;
	_funcptr_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)IntGetProcAddress("glGetSamplerParameteriv");
	if(!_funcptr_glGetSamplerParameteriv) ++numFailed;
	_funcptr_glIsSampler = (PFNGLISSAMPLERPROC)IntGetProcAddress("glIsSampler");
	if(!_funcptr_glIsSampler) ++numFailed;
	_funcptr_glQueryCounter = (PFNGLQUERYCOUNTERPROC)IntGetProcAddress("glQueryCounter");
	if(!_funcptr_glQueryCounter) ++numFailed;
	_funcptr_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glSamplerParameterIiv");
	if(!_funcptr_glSamplerParameterIiv) ++numFailed;
	_funcptr_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glSamplerParameterIuiv");
	if(!_funcptr_glSamplerParameterIuiv) ++numFailed;
	_funcptr_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)IntGetProcAddress("glSamplerParameterf");
	if(!_funcptr_glSamplerParameterf) ++numFailed;
	_funcptr_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)IntGetProcAddress("glSamplerParameterfv");
	if(!_funcptr_glSamplerParameterfv) ++numFailed;
	_funcptr_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)IntGetProcAddress("glSamplerParameteri");
	if(!_funcptr_glSamplerParameteri) ++numFailed;
	_funcptr_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)IntGetProcAddress("glSamplerParameteriv");
	if(!_funcptr_glSamplerParameteriv) ++numFailed;
	_funcptr_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)IntGetProcAddress("glVertexAttribDivisor");
	if(!_funcptr_glVertexAttribDivisor) ++numFailed;
	_funcptr_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)IntGetProcAddress("glVertexAttribP1ui");
	if(!_funcptr_glVertexAttribP1ui) ++numFailed;
	_funcptr_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)IntGetProcAddress("glVertexAttribP1uiv");
	if(!_funcptr_glVertexAttribP1uiv) ++numFailed;
	_funcptr_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)IntGetProcAddress("glVertexAttribP2ui");
	if(!_funcptr_glVertexAttribP2ui) ++numFailed;
	_funcptr_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)IntGetProcAddress("glVertexAttribP2uiv");
	if(!_funcptr_glVertexAttribP2uiv) ++numFailed;
	_funcptr_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)IntGetProcAddress("glVertexAttribP3ui");
	if(!_funcptr_glVertexAttribP3ui) ++numFailed;
	_funcptr_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)IntGetProcAddress("glVertexAttribP3uiv");
	if(!_funcptr_glVertexAttribP3uiv) ++numFailed;
	_funcptr_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)IntGetProcAddress("glVertexAttribP4ui");
	if(!_funcptr_glVertexAttribP4ui) ++numFailed;
	_funcptr_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)IntGetProcAddress("glVertexAttribP4uiv");
	if(!_funcptr_glVertexAttribP4uiv) ++numFailed;
	return numFailed;
}