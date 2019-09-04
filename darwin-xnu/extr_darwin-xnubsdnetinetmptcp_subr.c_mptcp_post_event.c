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
typedef  int /*<<< orphan*/  u_int32_t ;
struct kev_msg {TYPE_1__* dv; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_mptcp_data {int value; } ;
typedef  int /*<<< orphan*/  event_data ;
typedef  int /*<<< orphan*/  ev_msg ;
struct TYPE_2__ {int data_length; struct kev_mptcp_data* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_MPTCP_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int kev_post_msg (struct kev_msg*) ; 
 int /*<<< orphan*/  memset (struct kev_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mptcp_post_event(u_int32_t event_code, int value)
{
	struct kev_mptcp_data event_data;
	struct kev_msg ev_msg;

	memset(&ev_msg, 0, sizeof(ev_msg));

	ev_msg.vendor_code	= KEV_VENDOR_APPLE;
	ev_msg.kev_class	= KEV_NETWORK_CLASS;
	ev_msg.kev_subclass	= KEV_MPTCP_SUBCLASS;
	ev_msg.event_code	= event_code;

	event_data.value = value;

	ev_msg.dv[0].data_ptr	 = &event_data;
	ev_msg.dv[0].data_length = sizeof(event_data);

	return kev_post_msg(&ev_msg);
}