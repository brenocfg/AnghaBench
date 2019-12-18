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
struct xenbus_device {int /*<<< orphan*/  otherend_id; } ;
struct evtchn_bind_interdomain {int remote_port; int local_port; int /*<<< orphan*/  remote_dom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_interdomain ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_interdomain*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,int,int /*<<< orphan*/ ) ; 

int xenbus_bind_evtchn(struct xenbus_device *dev, int remote_port, int *port)
{
	struct evtchn_bind_interdomain bind_interdomain;
	int err;

	bind_interdomain.remote_dom = dev->otherend_id;
	bind_interdomain.remote_port = remote_port;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_bind_interdomain,
					  &bind_interdomain);
	if (err)
		xenbus_dev_fatal(dev, err,
				 "binding to event channel %d from domain %d",
				 remote_port, dev->otherend_id);
	else
		*port = bind_interdomain.local_port;

	return err;
}