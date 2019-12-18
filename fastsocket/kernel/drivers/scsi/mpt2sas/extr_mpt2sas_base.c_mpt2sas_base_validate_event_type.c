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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct MPT2SAS_ADAPTER {int* event_masks; TYPE_1__ base_cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_SLEEP ; 
 int MPI2_EVENT_NOTIFY_EVENTMASK_WORDS ; 
 int /*<<< orphan*/  _base_event_notification (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
mpt2sas_base_validate_event_type(struct MPT2SAS_ADAPTER *ioc, u32 *event_type)
{
	int i, j;
	u32 event_mask, desired_event;
	u8 send_update_to_fw;

	for (i = 0, send_update_to_fw = 0; i <
	    MPI2_EVENT_NOTIFY_EVENTMASK_WORDS; i++) {
		event_mask = ~event_type[i];
		desired_event = 1;
		for (j = 0; j < 32; j++) {
			if (!(event_mask & desired_event) &&
			    (ioc->event_masks[i] & desired_event)) {
				ioc->event_masks[i] &= ~desired_event;
				send_update_to_fw = 1;
			}
			desired_event = (desired_event << 1);
		}
	}

	if (!send_update_to_fw)
		return;

	mutex_lock(&ioc->base_cmds.mutex);
	_base_event_notification(ioc, CAN_SLEEP);
	mutex_unlock(&ioc->base_cmds.mutex);
}