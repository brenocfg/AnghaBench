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
struct TYPE_3__ {int Channels; long bchannel_trace_mask; } ;
typedef  TYPE_1__ diva_strace_context_t ;

/* Variables and functions */
 int ScheduleNextTraceRequest (TYPE_1__*) ; 

__attribute__((used)) static int SuperTraceSetBChannel  (void* hLib, int Channel, int on) {
	diva_strace_context_t* pLib = (diva_strace_context_t*)hLib;

	if ((Channel < 1) || (Channel > pLib->Channels)) {
		return (-1);
	}
	Channel--;

	if (on) {
		pLib->bchannel_trace_mask |=  (1L << Channel);
	} else {
		pLib->bchannel_trace_mask &= ~(1L << Channel);
	}

	return (ScheduleNextTraceRequest (pLib));
}