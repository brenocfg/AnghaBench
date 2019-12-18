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
typedef  scalar_t__ PFNGLVERTEXPOINTERPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERPROC ;
typedef  scalar_t__ PFNGLPUSHCLIENTATTRIBPROC ;
typedef  scalar_t__ PFNGLPRIORITIZETEXTURESPROC ;
typedef  scalar_t__ PFNGLPOPCLIENTATTRIBPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERPROC ;
typedef  scalar_t__ PFNGLINTERLEAVEDARRAYSPROC ;
typedef  scalar_t__ PFNGLINDEXUBVPROC ;
typedef  scalar_t__ PFNGLINDEXUBPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTERPROC ;
typedef  scalar_t__ PFNGLENABLECLIENTSTATEPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTERPROC ;
typedef  scalar_t__ PFNGLDISABLECLIENTSTATEPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERPROC ;
typedef  scalar_t__ PFNGLARRAYELEMENTPROC ;
typedef  scalar_t__ PFNGLARETEXTURESRESIDENTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glAreTexturesResident ; 
 scalar_t__ _funcptr_glArrayElement ; 
 scalar_t__ _funcptr_glColorPointer ; 
 scalar_t__ _funcptr_glDisableClientState ; 
 scalar_t__ _funcptr_glEdgeFlagPointer ; 
 scalar_t__ _funcptr_glEnableClientState ; 
 scalar_t__ _funcptr_glIndexPointer ; 
 scalar_t__ _funcptr_glIndexub ; 
 scalar_t__ _funcptr_glIndexubv ; 
 scalar_t__ _funcptr_glInterleavedArrays ; 
 scalar_t__ _funcptr_glNormalPointer ; 
 scalar_t__ _funcptr_glPopClientAttrib ; 
 scalar_t__ _funcptr_glPrioritizeTextures ; 
 scalar_t__ _funcptr_glPushClientAttrib ; 
 scalar_t__ _funcptr_glTexCoordPointer ; 
 scalar_t__ _funcptr_glVertexPointer ; 

__attribute__((used)) static int LoadCore_Version_1_1_Comp()
{
	int numFailed = 0;
	_funcptr_glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)IntGetProcAddress("glAreTexturesResident");
	if(!_funcptr_glAreTexturesResident) ++numFailed;
	_funcptr_glArrayElement = (PFNGLARRAYELEMENTPROC)IntGetProcAddress("glArrayElement");
	if(!_funcptr_glArrayElement) ++numFailed;
	_funcptr_glColorPointer = (PFNGLCOLORPOINTERPROC)IntGetProcAddress("glColorPointer");
	if(!_funcptr_glColorPointer) ++numFailed;
	_funcptr_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)IntGetProcAddress("glDisableClientState");
	if(!_funcptr_glDisableClientState) ++numFailed;
	_funcptr_glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)IntGetProcAddress("glEdgeFlagPointer");
	if(!_funcptr_glEdgeFlagPointer) ++numFailed;
	_funcptr_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)IntGetProcAddress("glEnableClientState");
	if(!_funcptr_glEnableClientState) ++numFailed;
	_funcptr_glIndexPointer = (PFNGLINDEXPOINTERPROC)IntGetProcAddress("glIndexPointer");
	if(!_funcptr_glIndexPointer) ++numFailed;
	_funcptr_glIndexub = (PFNGLINDEXUBPROC)IntGetProcAddress("glIndexub");
	if(!_funcptr_glIndexub) ++numFailed;
	_funcptr_glIndexubv = (PFNGLINDEXUBVPROC)IntGetProcAddress("glIndexubv");
	if(!_funcptr_glIndexubv) ++numFailed;
	_funcptr_glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)IntGetProcAddress("glInterleavedArrays");
	if(!_funcptr_glInterleavedArrays) ++numFailed;
	_funcptr_glNormalPointer = (PFNGLNORMALPOINTERPROC)IntGetProcAddress("glNormalPointer");
	if(!_funcptr_glNormalPointer) ++numFailed;
	_funcptr_glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)IntGetProcAddress("glPopClientAttrib");
	if(!_funcptr_glPopClientAttrib) ++numFailed;
	_funcptr_glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)IntGetProcAddress("glPrioritizeTextures");
	if(!_funcptr_glPrioritizeTextures) ++numFailed;
	_funcptr_glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)IntGetProcAddress("glPushClientAttrib");
	if(!_funcptr_glPushClientAttrib) ++numFailed;
	_funcptr_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)IntGetProcAddress("glTexCoordPointer");
	if(!_funcptr_glTexCoordPointer) ++numFailed;
	_funcptr_glVertexPointer = (PFNGLVERTEXPOINTERPROC)IntGetProcAddress("glVertexPointer");
	if(!_funcptr_glVertexPointer) ++numFailed;
	return numFailed;
}