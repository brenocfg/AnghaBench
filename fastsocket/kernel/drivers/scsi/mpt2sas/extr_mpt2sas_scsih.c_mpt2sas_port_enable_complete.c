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
struct fw_event_work {struct MPT2SAS_ADAPTER* ioc; int /*<<< orphan*/  event; } ;
struct MPT2SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MPT2SAS_PORT_ENABLE_COMPLETE ; 
 int /*<<< orphan*/  _scsih_fw_event_add (struct MPT2SAS_ADAPTER*,struct fw_event_work*) ; 
 struct fw_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 

void
mpt2sas_port_enable_complete(struct MPT2SAS_ADAPTER *ioc)
{
	struct fw_event_work *fw_event;

	fw_event = kzalloc(sizeof(struct fw_event_work), GFP_ATOMIC);
	if (!fw_event)
		return;
	fw_event->event = MPT2SAS_PORT_ENABLE_COMPLETE;
	fw_event->ioc = ioc;
	_scsih_fw_event_add(ioc, fw_event);
}