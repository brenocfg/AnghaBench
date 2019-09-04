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
struct kpc_get_counters_remote {int nb_counters; int /*<<< orphan*/  buf_stride; int /*<<< orphan*/ * buf; int /*<<< orphan*/  classes; } ;
struct TYPE_2__ {int cpu_id; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_broadcast_xcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpc_get_counters_remote*) ; 
 TYPE_1__* current_processor () ; 
 int /*<<< orphan*/  kpc_get_counter_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_curcpu_counters_xcall ; 
 int /*<<< orphan*/  kpc_xread_sync ; 
 int ml_set_interrupts_enabled (int) ; 

int
kpc_get_all_cpus_counters(uint32_t classes, int *curcpu, uint64_t *buf)
{
	assert(buf != NULL);

	int enabled = ml_set_interrupts_enabled(FALSE);

	/* grab counters and CPU number as close as possible */
	if (curcpu) {
		*curcpu = current_processor()->cpu_id;
	}

	struct kpc_get_counters_remote hdl = {
		.classes = classes,
		.nb_counters = 0,
		.buf = buf,
		.buf_stride = kpc_get_counter_count(classes)
	};

	cpu_broadcast_xcall(&kpc_xread_sync, TRUE, kpc_get_curcpu_counters_xcall, &hdl);
	int offset = hdl.nb_counters;

	(void)ml_set_interrupts_enabled(enabled);

	return offset;
}