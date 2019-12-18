#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int addr; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_3__ kp; } ;
struct TYPE_4__ {int /*<<< orphan*/  system; int /*<<< orphan*/  name; } ;
struct trace_probe {int /*<<< orphan*/  list; TYPE_2__ rp; TYPE_1__ call; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  KPROBE_FLAG_DISABLED ; 
 struct trace_probe* find_trace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_trace_probe (struct trace_probe*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  probe_list ; 
 int /*<<< orphan*/  probe_lock ; 
 int register_kprobe (TYPE_3__*) ; 
 int register_kretprobe (TYPE_2__*) ; 
 int register_probe_event (struct trace_probe*) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 
 int /*<<< orphan*/  unregister_probe_event (struct trace_probe*) ; 
 int unregister_trace_probe (struct trace_probe*) ; 

__attribute__((used)) static int register_trace_probe(struct trace_probe *tp)
{
	struct trace_probe *old_tp;
	int ret;

	mutex_lock(&probe_lock);

	/* register as an event */
	old_tp = find_trace_probe(tp->call.name, tp->call.system);
	if (old_tp) {
		/* delete old event */
		ret = unregister_trace_probe(old_tp);
		if (ret < 0)
			goto end;
		free_trace_probe(old_tp);
	}
	ret = register_probe_event(tp);
	if (ret) {
		pr_warning("Failed to register probe event(%d)\n", ret);
		goto end;
	}

	tp->rp.kp.flags |= KPROBE_FLAG_DISABLED;
	if (trace_probe_is_return(tp))
		ret = register_kretprobe(&tp->rp);
	else
		ret = register_kprobe(&tp->rp.kp);

	if (ret) {
		pr_warning("Could not insert probe(%d)\n", ret);
		if (ret == -EILSEQ) {
			pr_warning("Probing address(0x%p) is not an "
				   "instruction boundary.\n",
				   tp->rp.kp.addr);
			ret = -EINVAL;
		}
		unregister_probe_event(tp);
	} else
		list_add_tail(&tp->list, &probe_list);
end:
	mutex_unlock(&probe_lock);
	return ret;
}