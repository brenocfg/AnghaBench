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
typedef  int /*<<< orphan*/  unwind_entry_cb_t ;
typedef  int /*<<< orphan*/  unw_word_t ;
typedef  int /*<<< orphan*/  u64 ;
struct unwind_info {struct machine* machine; struct thread* thread; int /*<<< orphan*/  sample_uregs; struct perf_sample* sample; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct perf_sample {TYPE_1__ user_regs; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_REG_IP ; 
 int entry (int /*<<< orphan*/ ,struct thread*,struct machine*,int /*<<< orphan*/ ,void*) ; 
 int get_entries (struct unwind_info*,int /*<<< orphan*/ ,void*) ; 
 int reg_value (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unwind__get_entries(unwind_entry_cb_t cb, void *arg,
			struct machine *machine, struct thread *thread,
			u64 sample_uregs, struct perf_sample *data)
{
	unw_word_t ip;
	struct unwind_info ui = {
		.sample       = data,
		.sample_uregs = sample_uregs,
		.thread       = thread,
		.machine      = machine,
	};
	int ret;

	if (!data->user_regs.regs)
		return -EINVAL;

	ret = reg_value(&ip, &data->user_regs, PERF_REG_IP, sample_uregs);
	if (ret)
		return ret;

	ret = entry(ip, thread, machine, cb, arg);
	if (ret)
		return -ENOMEM;

	return get_entries(&ui, cb, arg);
}