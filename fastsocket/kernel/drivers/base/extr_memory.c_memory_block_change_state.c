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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct memory_block {unsigned long state; int start_phys_index; int end_phys_index; int /*<<< orphan*/  state_mutex; TYPE_1__ sysdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KOBJ_OFFLINE ; 
 int /*<<< orphan*/  KOBJ_ONLINE ; 
 unsigned long MEM_GOING_OFFLINE ; 
#define  MEM_OFFLINE 129 
#define  MEM_ONLINE 128 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int memory_section_action (int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int memory_block_change_state(struct memory_block *mem,
		unsigned long to_state, unsigned long from_state_req)
{
	int i, ret = 0;
	mutex_lock(&mem->state_mutex);

	if (mem->state != from_state_req) {
		ret = -EINVAL;
		goto out;
	}

	if (to_state == MEM_OFFLINE)
		mem->state = MEM_GOING_OFFLINE;

	for (i = mem->start_phys_index; i <= mem->end_phys_index; i++) {
		ret = memory_section_action(i, to_state);
		if (ret)
			break;
	}

	if (ret) {
		for (i = mem->start_phys_index; i <= mem->end_phys_index; i++)
			memory_section_action(i, from_state_req);

		mem->state = from_state_req;
		goto out;
	}

	mem->state = to_state;
	switch (mem->state) {
	case MEM_OFFLINE:
		kobject_uevent(&mem->sysdev.kobj, KOBJ_OFFLINE);
		break;
	case MEM_ONLINE:
		kobject_uevent(&mem->sysdev.kobj, KOBJ_ONLINE);
		break;
	default:
		break;
	}
out:
	mutex_unlock(&mem->state_mutex);
	return ret;
}