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
struct trace_probe {int /*<<< orphan*/  list; TYPE_1__ rp; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_probe_is_enabled (struct trace_probe*) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 
 int /*<<< orphan*/  unregister_kprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_kretprobe (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_probe_event (struct trace_probe*) ; 

__attribute__((used)) static int unregister_trace_probe(struct trace_probe *tp)
{
	/* Enabled event can not be unregistered */
	if (trace_probe_is_enabled(tp))
		return -EBUSY;

	if (trace_probe_is_return(tp))
		unregister_kretprobe(&tp->rp);
	else
		unregister_kprobe(&tp->rp.kp);
	list_del(&tp->list);
	unregister_probe_event(tp);

	return 0;
}