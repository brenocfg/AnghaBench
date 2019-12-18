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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kpc_get_counters_remote {int nb_counters; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buf_stride; int /*<<< orphan*/  classes; } ;
struct TYPE_2__ {int cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 int FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__* current_processor () ; 
 int /*<<< orphan*/  kpc_get_counter_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_curcpu_counters_mp_call ; 
 int ml_set_interrupts_enabled (int) ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpc_get_counters_remote*) ; 

int
kpc_get_all_cpus_counters(uint32_t classes, int *curcpu, uint64_t *buf)
{
	int enabled = 0;

	struct kpc_get_counters_remote hdl = {
		.classes = classes, .nb_counters = 0,
		.buf_stride = kpc_get_counter_count(classes), .buf = buf
	};

	assert(buf);

	enabled = ml_set_interrupts_enabled(FALSE);

	if (curcpu)
		*curcpu = current_processor()->cpu_id;
	mp_cpus_call(CPUMASK_ALL, ASYNC, kpc_get_curcpu_counters_mp_call, &hdl);

	ml_set_interrupts_enabled(enabled);

	return hdl.nb_counters;
}