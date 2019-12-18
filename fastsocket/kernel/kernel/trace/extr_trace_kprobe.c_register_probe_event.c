#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  trace; } ;
struct TYPE_4__ {int /*<<< orphan*/  print_fmt; } ;
struct ftrace_event_call {TYPE_1__ fmt; int /*<<< orphan*/  name; struct trace_probe* data; int /*<<< orphan*/  profile_disable; int /*<<< orphan*/  profile_enable; int /*<<< orphan*/  profile_count; int /*<<< orphan*/  unregfunc; int /*<<< orphan*/  regfunc; scalar_t__ enabled; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; TYPE_2__* event; int /*<<< orphan*/  define_fields; void* raw_init; } ;
struct trace_probe {TYPE_2__ event; struct ftrace_event_call call; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_KABI_PRINT_FMT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprobe_event_define_fields ; 
 int /*<<< orphan*/  kretprobe_event_define_fields ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_kprobe_event ; 
 int /*<<< orphan*/  print_kretprobe_event ; 
 int /*<<< orphan*/  probe_event_disable ; 
 int /*<<< orphan*/  probe_event_enable ; 
 void* probe_event_raw_init ; 
 int /*<<< orphan*/  probe_profile_disable ; 
 int /*<<< orphan*/  probe_profile_enable ; 
 int /*<<< orphan*/  register_ftrace_event (TYPE_2__*) ; 
 scalar_t__ set_print_fmt (struct trace_probe*) ; 
 int trace_add_event_call (struct ftrace_event_call*) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 
 int /*<<< orphan*/  unregister_ftrace_event (TYPE_2__*) ; 

__attribute__((used)) static int register_probe_event(struct trace_probe *tp)
{
	struct ftrace_event_call *call = &tp->call;
	int ret;

	/* Initialize ftrace_event_call */
	if (trace_probe_is_return(tp)) {
		tp->event.trace = print_kretprobe_event;
		call->raw_init = probe_event_raw_init;
		call->define_fields = kretprobe_event_define_fields;
	} else {
		tp->event.trace = print_kprobe_event;
		call->raw_init = probe_event_raw_init;
		call->define_fields = kprobe_event_define_fields;
	}
	if (set_print_fmt(tp) < 0)
		return -ENOMEM;
	call->event = &tp->event;
	call->id = register_ftrace_event(&tp->event);
	call->flags = TRACE_EVENT_FL_KABI_PRINT_FMT;
	if (!call->id) {
		kfree(call->fmt.print_fmt);
		return -ENODEV;
	}
	call->enabled = 0;
	call->regfunc = probe_event_enable;
	call->unregfunc = probe_event_disable;

#ifdef CONFIG_EVENT_PROFILE
	atomic_set(&call->profile_count, -1);
	call->profile_enable = probe_profile_enable;
	call->profile_disable = probe_profile_disable;
#endif
	call->data = tp;
	ret = trace_add_event_call(call);
	if (ret) {
		pr_info("Failed to register kprobe event: %s\n", call->name);
		kfree(call->fmt.print_fmt);
		unregister_ftrace_event(&tp->event);
	}
	return ret;
}