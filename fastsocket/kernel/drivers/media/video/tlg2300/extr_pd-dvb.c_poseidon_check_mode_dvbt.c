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
struct poseidon {int /*<<< orphan*/  udev; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_ALTERNATE_IFACE ; 
 int HZ ; 
 int /*<<< orphan*/  SGNL_SRC_SEL ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TLG_MODE_CAPS_DVB_T ; 
 int /*<<< orphan*/  TLG_SIG_SRC_ANTENNA ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int set_tuner_mode (struct poseidon*,int /*<<< orphan*/ ) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poseidon_check_mode_dvbt(struct poseidon *pd)
{
	s32 ret = 0, cmd_status = 0;

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ/4);

	ret = usb_set_interface(pd->udev, 0, BULK_ALTERNATE_IFACE);
	if (ret != 0)
		return ret;

	ret = set_tuner_mode(pd, TLG_MODE_CAPS_DVB_T);
	if (ret)
		return ret;

	/* signal source */
	ret = send_set_req(pd, SGNL_SRC_SEL, TLG_SIG_SRC_ANTENNA, &cmd_status);
	if (ret|cmd_status)
		return ret;

	return 0;
}