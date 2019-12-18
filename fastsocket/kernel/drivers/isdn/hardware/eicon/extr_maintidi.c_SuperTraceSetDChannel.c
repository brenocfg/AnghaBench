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
struct TYPE_3__ {int trace_event_mask; } ;
typedef  TYPE_1__ diva_strace_context_t ;

/* Variables and functions */
 int ScheduleNextTraceRequest (TYPE_1__*) ; 
 int TM_C_COMM ; 
 int TM_DL_ERR ; 
 int TM_D_CHAN ; 
 int TM_LAYER1 ; 

__attribute__((used)) static int SuperTraceSetDChannel  (void* hLib, int on) {
	diva_strace_context_t* pLib = (diva_strace_context_t*)hLib;

	if (on) {
		pLib->trace_event_mask |= (TM_D_CHAN | TM_C_COMM | TM_DL_ERR | TM_LAYER1);
	} else {
		pLib->trace_event_mask &= ~(TM_D_CHAN | TM_C_COMM | TM_DL_ERR | TM_LAYER1);
	}

	return (ScheduleNextTraceRequest (pLib));
}