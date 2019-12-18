#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* control; } ;
struct usb_line6_pod {int /*<<< orphan*/  line6; TYPE_1__ prog_data; } ;
struct ValueWait {scalar_t__ value; int /*<<< orphan*/  wait; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  POD_SYSEX_SYSTEMREQ ; 
 scalar_t__ POD_system_invalid ; 
 size_t POD_tuner ; 
 size_t SYSEX_DATA_OFS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  line6_send_sysex_message (int /*<<< orphan*/ *,char*,int const) ; 
 char* pod_alloc_sysex_buffer (struct usb_line6_pod*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t pod_get_system_param(struct usb_line6_pod *pod, char *buf, int code, struct ValueWait *param, int tuner, int sign)
{
	char *sysex;
	int value;
	static const int size = 1;
	int retval = 0;
	DECLARE_WAITQUEUE(wait, current);

	if (((pod->prog_data.control[POD_tuner] & 0x40) == 0) && tuner)
		return -ENODEV;

	/* send value request to tuner: */
	param->value = POD_system_invalid;
	sysex = pod_alloc_sysex_buffer(pod, POD_SYSEX_SYSTEMREQ, size);
	if (!sysex)
		return 0;
	sysex[SYSEX_DATA_OFS] = code;
	line6_send_sysex_message(&pod->line6, sysex, size);
	kfree(sysex);

	/* wait for tuner to respond: */
	add_wait_queue(&param->wait, &wait);
	current->state = TASK_INTERRUPTIBLE;

	while (param->value == POD_system_invalid) {
		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		} else
			schedule();
	}

	current->state = TASK_RUNNING;
	remove_wait_queue(&param->wait, &wait);

	if (retval < 0)
		return retval;

	value = sign ? (int)(signed short)param->value : (int)(unsigned short)param->value;
	return sprintf(buf, "%d\n", value);
}