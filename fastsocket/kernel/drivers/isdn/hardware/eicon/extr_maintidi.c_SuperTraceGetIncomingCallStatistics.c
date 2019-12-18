#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int incoming_ifc_stats; } ;
typedef  TYPE_1__ diva_strace_context_t ;

/* Variables and functions */
 int ScheduleNextTraceRequest (TYPE_1__*) ; 

__attribute__((used)) static int SuperTraceGetIncomingCallStatistics (void* hLib) {
	diva_strace_context_t* pLib = (diva_strace_context_t*)hLib;
	pLib->incoming_ifc_stats = 1;
	return (ScheduleNextTraceRequest (pLib));
}