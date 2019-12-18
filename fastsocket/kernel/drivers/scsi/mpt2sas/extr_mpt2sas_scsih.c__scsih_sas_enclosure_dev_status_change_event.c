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
struct fw_event_work {int /*<<< orphan*/  event_data; } ;
struct MPT2SAS_ADAPTER {int logging_level; } ;

/* Variables and functions */
 int MPT_DEBUG_EVENT_WORK_TASK ; 
 int /*<<< orphan*/  _scsih_sas_enclosure_dev_status_change_event_debug (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_enclosure_dev_status_change_event(struct MPT2SAS_ADAPTER *ioc,
    struct fw_event_work *fw_event)
{
#ifdef CONFIG_SCSI_MPT2SAS_LOGGING
	if (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_sas_enclosure_dev_status_change_event_debug(ioc,
		     fw_event->event_data);
#endif
}