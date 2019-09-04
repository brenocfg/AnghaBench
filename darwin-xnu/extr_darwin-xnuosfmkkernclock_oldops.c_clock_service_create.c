#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct alarm {int dummy; } ;
typedef  TYPE_1__* clock_t ;
struct TYPE_5__ {scalar_t__ cl_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  alarm_zone ; 
 int clock_count ; 
 TYPE_1__* clock_list ; 
 int /*<<< orphan*/  ipc_clock_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_clock_init (TYPE_1__*) ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 

void
clock_service_create(void)
{
	clock_t			clock;
	int	i;

	/*
	 * Initialize ipc clock services.
	 */
	for (i = 0; i < clock_count; i++) {
		clock = &clock_list[i];
		if (clock->cl_ops) {
			ipc_clock_init(clock);
			ipc_clock_enable(clock);
		}
	}

	/*
	 * Perform miscellaneous late
	 * initialization.
	 */
	i = sizeof(struct alarm);
	alarm_zone = zinit(i, (4096/i)*i, 10*i, "alarms");
}