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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
struct perfcontrol_thread_data {int /*<<< orphan*/  perfctl_state; int /*<<< orphan*/  scheduling_latency_at_same_basepri; int /*<<< orphan*/  thread_id; scalar_t__ energy_estimate_nj; int /*<<< orphan*/  perfctl_class; } ;
struct TYPE_5__ {int /*<<< orphan*/  thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_PERFCONTROL_STATE (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (struct perfcontrol_thread_data*,int) ; 
 int /*<<< orphan*/  thread_get_perfcontrol_class (TYPE_1__*) ; 

__attribute__((used)) static void
machine_switch_populate_perfcontrol_thread_data(struct perfcontrol_thread_data *data, 
						thread_t thread,
						uint64_t same_pri_latency)
{
	bzero(data, sizeof(struct perfcontrol_thread_data));
	data->perfctl_class = thread_get_perfcontrol_class(thread);
	data->energy_estimate_nj = 0;
	data->thread_id = thread->thread_id;
	data->scheduling_latency_at_same_basepri = same_pri_latency;
	data->perfctl_state = FIND_PERFCONTROL_STATE(thread);
}