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
struct TYPE_2__ {scalar_t__ last_guard_val; scalar_t__ ctx_sw_seen; } ;

/* Variables and functions */
 int ESCAPE_CODE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SKIP_GENERIC_SYNC ; 
 int SPU_PROFILING_CODE ; 
 int SYNC_START_ERROR ; 
 int /*<<< orphan*/  buffer_lock ; 
 int num_spu_nodes ; 
 int number_of_online_nodes () ; 
 int oprofile_spu_buff_create () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spu_active ; 
 TYPE_1__* spu_buff ; 
 int /*<<< orphan*/  spu_buff_add (int,int) ; 
 int spu_prof_num_nodes ; 
 int spu_switch_event_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_work ; 
 int /*<<< orphan*/  wq_sync_spu_buff ; 

int spu_sync_start(void)
{
	int spu;
	int ret = SKIP_GENERIC_SYNC;
	int register_ret;
	unsigned long flags = 0;

	spu_prof_num_nodes = number_of_online_nodes();
	num_spu_nodes = spu_prof_num_nodes * 8;
	INIT_DELAYED_WORK(&spu_work, wq_sync_spu_buff);

	/* create buffer for storing the SPU data to put in
	 * the kernel buffer.
	 */
	ret = oprofile_spu_buff_create();
	if (ret)
		goto out;

	spin_lock_irqsave(&buffer_lock, flags);
	for (spu = 0; spu < num_spu_nodes; spu++) {
		spu_buff_add(ESCAPE_CODE, spu);
		spu_buff_add(SPU_PROFILING_CODE, spu);
		spu_buff_add(num_spu_nodes, spu);
	}
	spin_unlock_irqrestore(&buffer_lock, flags);

	for (spu = 0; spu < num_spu_nodes; spu++) {
		spu_buff[spu].ctx_sw_seen = 0;
		spu_buff[spu].last_guard_val = 0;
	}

	/* Register for SPU events  */
	register_ret = spu_switch_event_register(&spu_active);
	if (register_ret) {
		ret = SYNC_START_ERROR;
		goto out;
	}

	pr_debug("spu_sync_start -- running.\n");
out:
	return ret;
}