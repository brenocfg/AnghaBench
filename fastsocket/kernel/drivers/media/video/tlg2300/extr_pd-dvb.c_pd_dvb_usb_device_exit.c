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
struct pd_dvb_adapter {int /*<<< orphan*/  dvb_adap; int /*<<< orphan*/  dvb_fe; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  active_feed; int /*<<< orphan*/  users; } ;
struct poseidon {struct pd_dvb_adapter dvb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_dvb_usb_device_cleanup (struct poseidon*) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

void pd_dvb_usb_device_exit(struct poseidon *pd)
{
	struct pd_dvb_adapter *pd_dvb = &pd->dvb_data;

	while (atomic_read(&pd_dvb->users) != 0
		|| atomic_read(&pd_dvb->active_feed) != 0) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(HZ);
	}
	dvb_dmxdev_release(&pd_dvb->dmxdev);
	dvb_unregister_frontend(&pd_dvb->dvb_fe);
	dvb_unregister_adapter(&pd_dvb->dvb_adap);
	pd_dvb_usb_device_cleanup(pd);
}