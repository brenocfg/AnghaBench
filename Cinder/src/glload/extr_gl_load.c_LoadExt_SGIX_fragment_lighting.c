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
typedef  scalar_t__ PFNGLLIGHTENVISGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTMATERIALIVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTMATERIALFVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTLIGHTIVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTLIGHTFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTCOLORMATERIALSGIXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glFragmentColorMaterialSGIX ; 
 scalar_t__ _funcptr_glFragmentLightModelfSGIX ; 
 scalar_t__ _funcptr_glFragmentLightModelfvSGIX ; 
 scalar_t__ _funcptr_glFragmentLightModeliSGIX ; 
 scalar_t__ _funcptr_glFragmentLightModelivSGIX ; 
 scalar_t__ _funcptr_glFragmentLightfSGIX ; 
 scalar_t__ _funcptr_glFragmentLightfvSGIX ; 
 scalar_t__ _funcptr_glFragmentLightiSGIX ; 
 scalar_t__ _funcptr_glFragmentLightivSGIX ; 
 scalar_t__ _funcptr_glFragmentMaterialfSGIX ; 
 scalar_t__ _funcptr_glFragmentMaterialfvSGIX ; 
 scalar_t__ _funcptr_glFragmentMaterialiSGIX ; 
 scalar_t__ _funcptr_glFragmentMaterialivSGIX ; 
 scalar_t__ _funcptr_glGetFragmentLightfvSGIX ; 
 scalar_t__ _funcptr_glGetFragmentLightivSGIX ; 
 scalar_t__ _funcptr_glGetFragmentMaterialfvSGIX ; 
 scalar_t__ _funcptr_glGetFragmentMaterialivSGIX ; 
 scalar_t__ _funcptr_glLightEnviSGIX ; 

__attribute__((used)) static int LoadExt_SGIX_fragment_lighting()
{
	int numFailed = 0;
	_funcptr_glFragmentColorMaterialSGIX = (PFNGLFRAGMENTCOLORMATERIALSGIXPROC)IntGetProcAddress("glFragmentColorMaterialSGIX");
	if(!_funcptr_glFragmentColorMaterialSGIX) ++numFailed;
	_funcptr_glFragmentLightModelfSGIX = (PFNGLFRAGMENTLIGHTMODELFSGIXPROC)IntGetProcAddress("glFragmentLightModelfSGIX");
	if(!_funcptr_glFragmentLightModelfSGIX) ++numFailed;
	_funcptr_glFragmentLightModelfvSGIX = (PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)IntGetProcAddress("glFragmentLightModelfvSGIX");
	if(!_funcptr_glFragmentLightModelfvSGIX) ++numFailed;
	_funcptr_glFragmentLightModeliSGIX = (PFNGLFRAGMENTLIGHTMODELISGIXPROC)IntGetProcAddress("glFragmentLightModeliSGIX");
	if(!_funcptr_glFragmentLightModeliSGIX) ++numFailed;
	_funcptr_glFragmentLightModelivSGIX = (PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)IntGetProcAddress("glFragmentLightModelivSGIX");
	if(!_funcptr_glFragmentLightModelivSGIX) ++numFailed;
	_funcptr_glFragmentLightfSGIX = (PFNGLFRAGMENTLIGHTFSGIXPROC)IntGetProcAddress("glFragmentLightfSGIX");
	if(!_funcptr_glFragmentLightfSGIX) ++numFailed;
	_funcptr_glFragmentLightfvSGIX = (PFNGLFRAGMENTLIGHTFVSGIXPROC)IntGetProcAddress("glFragmentLightfvSGIX");
	if(!_funcptr_glFragmentLightfvSGIX) ++numFailed;
	_funcptr_glFragmentLightiSGIX = (PFNGLFRAGMENTLIGHTISGIXPROC)IntGetProcAddress("glFragmentLightiSGIX");
	if(!_funcptr_glFragmentLightiSGIX) ++numFailed;
	_funcptr_glFragmentLightivSGIX = (PFNGLFRAGMENTLIGHTIVSGIXPROC)IntGetProcAddress("glFragmentLightivSGIX");
	if(!_funcptr_glFragmentLightivSGIX) ++numFailed;
	_funcptr_glFragmentMaterialfSGIX = (PFNGLFRAGMENTMATERIALFSGIXPROC)IntGetProcAddress("glFragmentMaterialfSGIX");
	if(!_funcptr_glFragmentMaterialfSGIX) ++numFailed;
	_funcptr_glFragmentMaterialfvSGIX = (PFNGLFRAGMENTMATERIALFVSGIXPROC)IntGetProcAddress("glFragmentMaterialfvSGIX");
	if(!_funcptr_glFragmentMaterialfvSGIX) ++numFailed;
	_funcptr_glFragmentMaterialiSGIX = (PFNGLFRAGMENTMATERIALISGIXPROC)IntGetProcAddress("glFragmentMaterialiSGIX");
	if(!_funcptr_glFragmentMaterialiSGIX) ++numFailed;
	_funcptr_glFragmentMaterialivSGIX = (PFNGLFRAGMENTMATERIALIVSGIXPROC)IntGetProcAddress("glFragmentMaterialivSGIX");
	if(!_funcptr_glFragmentMaterialivSGIX) ++numFailed;
	_funcptr_glGetFragmentLightfvSGIX = (PFNGLGETFRAGMENTLIGHTFVSGIXPROC)IntGetProcAddress("glGetFragmentLightfvSGIX");
	if(!_funcptr_glGetFragmentLightfvSGIX) ++numFailed;
	_funcptr_glGetFragmentLightivSGIX = (PFNGLGETFRAGMENTLIGHTIVSGIXPROC)IntGetProcAddress("glGetFragmentLightivSGIX");
	if(!_funcptr_glGetFragmentLightivSGIX) ++numFailed;
	_funcptr_glGetFragmentMaterialfvSGIX = (PFNGLGETFRAGMENTMATERIALFVSGIXPROC)IntGetProcAddress("glGetFragmentMaterialfvSGIX");
	if(!_funcptr_glGetFragmentMaterialfvSGIX) ++numFailed;
	_funcptr_glGetFragmentMaterialivSGIX = (PFNGLGETFRAGMENTMATERIALIVSGIXPROC)IntGetProcAddress("glGetFragmentMaterialivSGIX");
	if(!_funcptr_glGetFragmentMaterialivSGIX) ++numFailed;
	_funcptr_glLightEnviSGIX = (PFNGLLIGHTENVISGIXPROC)IntGetProcAddress("glLightEnviSGIX");
	if(!_funcptr_glLightEnviSGIX) ++numFailed;
	return numFailed;
}