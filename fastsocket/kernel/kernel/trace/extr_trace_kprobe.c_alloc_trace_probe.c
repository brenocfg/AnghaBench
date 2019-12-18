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
struct TYPE_6__ {struct trace_probe* name; void* system; } ;
struct TYPE_4__ {unsigned long offset; int /*<<< orphan*/  pre_handler; void* addr; struct trace_probe* symbol_name; } ;
struct TYPE_5__ {TYPE_1__ kp; int /*<<< orphan*/  handler; } ;
struct trace_probe {struct trace_probe* symbol; TYPE_3__ call; int /*<<< orphan*/  list; TYPE_2__ rp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct trace_probe* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIZEOF_TRACE_PROBE (int) ; 
 int /*<<< orphan*/  is_good_name (char const*) ; 
 int /*<<< orphan*/  kfree (struct trace_probe*) ; 
 int /*<<< orphan*/  kprobe_dispatcher ; 
 int /*<<< orphan*/  kretprobe_dispatcher ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct trace_probe* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trace_probe *alloc_trace_probe(const char *group,
					     const char *event,
					     void *addr,
					     const char *symbol,
					     unsigned long offs,
					     int nargs, bool is_return)
{
	struct trace_probe *tp;
	int ret = -ENOMEM;

	tp = kzalloc(SIZEOF_TRACE_PROBE(nargs), GFP_KERNEL);
	if (!tp)
		return ERR_PTR(ret);

	if (symbol) {
		tp->symbol = kstrdup(symbol, GFP_KERNEL);
		if (!tp->symbol)
			goto error;
		tp->rp.kp.symbol_name = tp->symbol;
		tp->rp.kp.offset = offs;
	} else
		tp->rp.kp.addr = addr;

	if (is_return)
		tp->rp.handler = kretprobe_dispatcher;
	else
		tp->rp.kp.pre_handler = kprobe_dispatcher;

	if (!event || !is_good_name(event)) {
		ret = -EINVAL;
		goto error;
	}

	tp->call.name = kstrdup(event, GFP_KERNEL);
	if (!tp->call.name)
		goto error;

	if (!group || !is_good_name(group)) {
		ret = -EINVAL;
		goto error;
	}

	tp->call.system = kstrdup(group, GFP_KERNEL);
	if (!tp->call.system)
		goto error;

	INIT_LIST_HEAD(&tp->list);
	return tp;
error:
	kfree(tp->call.name);
	kfree(tp->symbol);
	kfree(tp);
	return ERR_PTR(ret);
}