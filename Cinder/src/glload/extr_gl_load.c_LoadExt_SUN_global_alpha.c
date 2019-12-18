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
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUSSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUISUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUBSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORSSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORISUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORFSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORDSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORBSUNPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGlobalAlphaFactorbSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactordSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactorfSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactoriSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactorsSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactorubSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactoruiSUN ; 
 scalar_t__ _funcptr_glGlobalAlphaFactorusSUN ; 

__attribute__((used)) static int LoadExt_SUN_global_alpha()
{
	int numFailed = 0;
	_funcptr_glGlobalAlphaFactorbSUN = (PFNGLGLOBALALPHAFACTORBSUNPROC)IntGetProcAddress("glGlobalAlphaFactorbSUN");
	if(!_funcptr_glGlobalAlphaFactorbSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactordSUN = (PFNGLGLOBALALPHAFACTORDSUNPROC)IntGetProcAddress("glGlobalAlphaFactordSUN");
	if(!_funcptr_glGlobalAlphaFactordSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactorfSUN = (PFNGLGLOBALALPHAFACTORFSUNPROC)IntGetProcAddress("glGlobalAlphaFactorfSUN");
	if(!_funcptr_glGlobalAlphaFactorfSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactoriSUN = (PFNGLGLOBALALPHAFACTORISUNPROC)IntGetProcAddress("glGlobalAlphaFactoriSUN");
	if(!_funcptr_glGlobalAlphaFactoriSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactorsSUN = (PFNGLGLOBALALPHAFACTORSSUNPROC)IntGetProcAddress("glGlobalAlphaFactorsSUN");
	if(!_funcptr_glGlobalAlphaFactorsSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactorubSUN = (PFNGLGLOBALALPHAFACTORUBSUNPROC)IntGetProcAddress("glGlobalAlphaFactorubSUN");
	if(!_funcptr_glGlobalAlphaFactorubSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactoruiSUN = (PFNGLGLOBALALPHAFACTORUISUNPROC)IntGetProcAddress("glGlobalAlphaFactoruiSUN");
	if(!_funcptr_glGlobalAlphaFactoruiSUN) ++numFailed;
	_funcptr_glGlobalAlphaFactorusSUN = (PFNGLGLOBALALPHAFACTORUSSUNPROC)IntGetProcAddress("glGlobalAlphaFactorusSUN");
	if(!_funcptr_glGlobalAlphaFactorusSUN) ++numFailed;
	return numFailed;
}