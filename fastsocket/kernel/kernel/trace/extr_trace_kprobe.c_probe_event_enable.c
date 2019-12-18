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
struct trace_probe {TYPE_1__ rp; int /*<<< orphan*/  flags; } ;
struct ftrace_event_call {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 int enable_kprobe (int /*<<< orphan*/ *) ; 
 int enable_kretprobe (TYPE_1__*) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 

__attribute__((used)) static int probe_event_enable(struct ftrace_event_call *call)
{
	struct trace_probe *tp = (struct trace_probe *)call->data;

	tp->flags |= TP_FLAG_TRACE;
	if (trace_probe_is_return(tp))
		return enable_kretprobe(&tp->rp);
	else
		return enable_kprobe(&tp->rp.kp);
}