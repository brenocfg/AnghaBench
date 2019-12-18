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
typedef  scalar_t__ PFNGLSTOPINSTRUMENTSSGIXPROC ;
typedef  scalar_t__ PFNGLSTARTINSTRUMENTSSGIXPROC ;
typedef  scalar_t__ PFNGLREADINSTRUMENTSSGIXPROC ;
typedef  scalar_t__ PFNGLPOLLINSTRUMENTSSGIXPROC ;
typedef  scalar_t__ PFNGLINSTRUMENTSBUFFERSGIXPROC ;
typedef  scalar_t__ PFNGLGETINSTRUMENTSSGIXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetInstrumentsSGIX ; 
 scalar_t__ _funcptr_glInstrumentsBufferSGIX ; 
 scalar_t__ _funcptr_glPollInstrumentsSGIX ; 
 scalar_t__ _funcptr_glReadInstrumentsSGIX ; 
 scalar_t__ _funcptr_glStartInstrumentsSGIX ; 
 scalar_t__ _funcptr_glStopInstrumentsSGIX ; 

__attribute__((used)) static int LoadExt_SGIX_instruments()
{
	int numFailed = 0;
	_funcptr_glGetInstrumentsSGIX = (PFNGLGETINSTRUMENTSSGIXPROC)IntGetProcAddress("glGetInstrumentsSGIX");
	if(!_funcptr_glGetInstrumentsSGIX) ++numFailed;
	_funcptr_glInstrumentsBufferSGIX = (PFNGLINSTRUMENTSBUFFERSGIXPROC)IntGetProcAddress("glInstrumentsBufferSGIX");
	if(!_funcptr_glInstrumentsBufferSGIX) ++numFailed;
	_funcptr_glPollInstrumentsSGIX = (PFNGLPOLLINSTRUMENTSSGIXPROC)IntGetProcAddress("glPollInstrumentsSGIX");
	if(!_funcptr_glPollInstrumentsSGIX) ++numFailed;
	_funcptr_glReadInstrumentsSGIX = (PFNGLREADINSTRUMENTSSGIXPROC)IntGetProcAddress("glReadInstrumentsSGIX");
	if(!_funcptr_glReadInstrumentsSGIX) ++numFailed;
	_funcptr_glStartInstrumentsSGIX = (PFNGLSTARTINSTRUMENTSSGIXPROC)IntGetProcAddress("glStartInstrumentsSGIX");
	if(!_funcptr_glStartInstrumentsSGIX) ++numFailed;
	_funcptr_glStopInstrumentsSGIX = (PFNGLSTOPINSTRUMENTSSGIXPROC)IntGetProcAddress("glStopInstrumentsSGIX");
	if(!_funcptr_glStopInstrumentsSGIX) ++numFailed;
	return numFailed;
}