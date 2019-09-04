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
typedef  int uint32_t ;
struct netpolicy_event_data {int dummy; } ;
struct kev_msg {int event_code; TYPE_1__* dv; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
typedef  int /*<<< orphan*/  ev_msg ;
struct TYPE_2__ {int data_length; struct netpolicy_event_data* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_NETPOLICY_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  kev_post_msg (struct kev_msg*) ; 

void
netpolicy_post_msg(uint32_t ev_code, struct netpolicy_event_data *ev_data,
    uint32_t ev_datalen)
{
	struct kev_msg ev_msg;

	/*
	 * A netpolicy event always starts with a netpolicy_event_data
	 * structure, but the caller can provide for a longer event
	 * structure to post, depending on the event code.
	 */
	VERIFY(ev_data != NULL && ev_datalen >= sizeof (*ev_data));

	bzero(&ev_msg, sizeof (ev_msg));
	ev_msg.vendor_code	= KEV_VENDOR_APPLE;
	ev_msg.kev_class	= KEV_NETWORK_CLASS;
	ev_msg.kev_subclass	= KEV_NETPOLICY_SUBCLASS;
	ev_msg.event_code	= ev_code;

	ev_msg.dv[0].data_ptr	= ev_data;
	ev_msg.dv[0].data_length = ev_datalen;

	kev_post_msg(&ev_msg);
}