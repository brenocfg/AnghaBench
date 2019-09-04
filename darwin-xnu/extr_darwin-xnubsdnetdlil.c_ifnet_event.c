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
struct kev_msg {TYPE_1__* dv; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kern_event_msg {scalar_t__ total_size; int /*<<< orphan*/ * event_data; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
typedef  int /*<<< orphan*/  kev_msg ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int errno_t ;
struct TYPE_2__ {scalar_t__ data_length; int /*<<< orphan*/ * data_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KEV_MSG_HEADER_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int dlil_event_internal (int /*<<< orphan*/ *,struct kev_msg*,int /*<<< orphan*/ ) ; 

errno_t
ifnet_event(ifnet_t ifp, struct kern_event_msg *event)
{
	struct kev_msg kev_msg;
	int result = 0;

	if (ifp == NULL || event == NULL)
		return (EINVAL);

	bzero(&kev_msg, sizeof (kev_msg));
	kev_msg.vendor_code = event->vendor_code;
	kev_msg.kev_class = event->kev_class;
	kev_msg.kev_subclass = event->kev_subclass;
	kev_msg.event_code = event->event_code;
	kev_msg.dv[0].data_ptr = &event->event_data[0];
	kev_msg.dv[0].data_length = event->total_size - KEV_MSG_HEADER_SIZE;
	kev_msg.dv[1].data_length = 0;

	result = dlil_event_internal(ifp, &kev_msg, TRUE);

	return (result);
}