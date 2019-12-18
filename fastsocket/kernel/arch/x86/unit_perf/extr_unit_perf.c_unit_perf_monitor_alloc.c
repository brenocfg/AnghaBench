#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct unit_perf_monitor {scalar_t__ list; scalar_t__ list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (scalar_t__) ; 
 scalar_t__ UNIT_PERF_SLOT_CNT ; 
 struct unit_perf_monitor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unit_perf_monitor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (scalar_t__) ; 

__attribute__((used)) static struct unit_perf_monitor * unit_perf_monitor_alloc(void)
{
	struct unit_perf_monitor *monitor;
	u32 i;

	monitor = kmalloc(sizeof(*monitor), GFP_KERNEL);
	if (!monitor) {
		return NULL;
	}
	memset(monitor, 0, sizeof(*monitor));

	for (i = 0; i < UNIT_PERF_SLOT_CNT; ++i) {
		INIT_LIST_HEAD(monitor->list+i);
		spin_lock_init(monitor->list_lock+i);
	}

	return monitor;
}