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
struct wf_sensor {int /*<<< orphan*/  name; } ;
struct wf_control {int /*<<< orphan*/  name; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
#define  WF_EVENT_NEW_CONTROL 130 
#define  WF_EVENT_NEW_SENSOR 129 
#define  WF_EVENT_TICK 128 
 int /*<<< orphan*/  wf_smu_all_controls_ok ; 
 int /*<<< orphan*/  wf_smu_all_sensors_ok ; 
 int /*<<< orphan*/  wf_smu_new_control (void*) ; 
 int /*<<< orphan*/  wf_smu_new_sensor (void*) ; 
 int wf_smu_readjust ; 
 int /*<<< orphan*/  wf_smu_tick () ; 

__attribute__((used)) static int wf_smu_notify(struct notifier_block *self,
			       unsigned long event, void *data)
{
	switch(event) {
	case WF_EVENT_NEW_CONTROL:
		DBG("wf: new control %s detected\n",
		    ((struct wf_control *)data)->name);
		wf_smu_new_control(data);
		wf_smu_readjust = 1;
		break;
	case WF_EVENT_NEW_SENSOR:
		DBG("wf: new sensor %s detected\n",
		    ((struct wf_sensor *)data)->name);
		wf_smu_new_sensor(data);
		break;
	case WF_EVENT_TICK:
		if (wf_smu_all_controls_ok && wf_smu_all_sensors_ok)
			wf_smu_tick();
	}

	return 0;
}