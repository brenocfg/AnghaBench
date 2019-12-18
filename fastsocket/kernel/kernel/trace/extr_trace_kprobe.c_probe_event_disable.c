#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kp; } ;
struct trace_probe {int flags; TYPE_1__ rp; } ;
struct ftrace_event_call {scalar_t__ data; } ;

/* Variables and functions */
 int TP_FLAG_PROFILE ; 
 int TP_FLAG_TRACE ; 
 int /*<<< orphan*/  disable_kprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_kretprobe (TYPE_1__*) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 

__attribute__((used)) static void probe_event_disable(struct ftrace_event_call *call)
{
	struct trace_probe *tp = (struct trace_probe *)call->data;

	tp->flags &= ~TP_FLAG_TRACE;
	if (!(tp->flags & (TP_FLAG_TRACE | TP_FLAG_PROFILE))) {
		if (trace_probe_is_return(tp))
			disable_kretprobe(&tp->rp);
		else
			disable_kprobe(&tp->rp.kp);
	}
}