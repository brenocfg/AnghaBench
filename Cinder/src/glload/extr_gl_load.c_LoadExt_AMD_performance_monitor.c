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
typedef  scalar_t__ PFNGLSELECTPERFMONITORCOUNTERSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORGROUPSTRINGAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORGROUPSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERINFOAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERDATAAMDPROC ;
typedef  scalar_t__ PFNGLGENPERFMONITORSAMDPROC ;
typedef  scalar_t__ PFNGLENDPERFMONITORAMDPROC ;
typedef  scalar_t__ PFNGLDELETEPERFMONITORSAMDPROC ;
typedef  scalar_t__ PFNGLBEGINPERFMONITORAMDPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginPerfMonitorAMD ; 
 scalar_t__ _funcptr_glDeletePerfMonitorsAMD ; 
 scalar_t__ _funcptr_glEndPerfMonitorAMD ; 
 scalar_t__ _funcptr_glGenPerfMonitorsAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorCounterDataAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorCounterInfoAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorCounterStringAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorCountersAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorGroupStringAMD ; 
 scalar_t__ _funcptr_glGetPerfMonitorGroupsAMD ; 
 scalar_t__ _funcptr_glSelectPerfMonitorCountersAMD ; 

__attribute__((used)) static int LoadExt_AMD_performance_monitor()
{
	int numFailed = 0;
	_funcptr_glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC)IntGetProcAddress("glBeginPerfMonitorAMD");
	if(!_funcptr_glBeginPerfMonitorAMD) ++numFailed;
	_funcptr_glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC)IntGetProcAddress("glDeletePerfMonitorsAMD");
	if(!_funcptr_glDeletePerfMonitorsAMD) ++numFailed;
	_funcptr_glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC)IntGetProcAddress("glEndPerfMonitorAMD");
	if(!_funcptr_glEndPerfMonitorAMD) ++numFailed;
	_funcptr_glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC)IntGetProcAddress("glGenPerfMonitorsAMD");
	if(!_funcptr_glGenPerfMonitorsAMD) ++numFailed;
	_funcptr_glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)IntGetProcAddress("glGetPerfMonitorCounterDataAMD");
	if(!_funcptr_glGetPerfMonitorCounterDataAMD) ++numFailed;
	_funcptr_glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)IntGetProcAddress("glGetPerfMonitorCounterInfoAMD");
	if(!_funcptr_glGetPerfMonitorCounterInfoAMD) ++numFailed;
	_funcptr_glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)IntGetProcAddress("glGetPerfMonitorCounterStringAMD");
	if(!_funcptr_glGetPerfMonitorCounterStringAMD) ++numFailed;
	_funcptr_glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC)IntGetProcAddress("glGetPerfMonitorCountersAMD");
	if(!_funcptr_glGetPerfMonitorCountersAMD) ++numFailed;
	_funcptr_glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)IntGetProcAddress("glGetPerfMonitorGroupStringAMD");
	if(!_funcptr_glGetPerfMonitorGroupStringAMD) ++numFailed;
	_funcptr_glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC)IntGetProcAddress("glGetPerfMonitorGroupsAMD");
	if(!_funcptr_glGetPerfMonitorGroupsAMD) ++numFailed;
	_funcptr_glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)IntGetProcAddress("glSelectPerfMonitorCountersAMD");
	if(!_funcptr_glSelectPerfMonitorCountersAMD) ++numFailed;
	return numFailed;
}