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
typedef  void* u_int32_t ;
struct kev_msg {TYPE_1__* dv; void* ctl_id; void* event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct ctl_event_data {TYPE_1__* dv; void* ctl_id; void* event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
typedef  int /*<<< orphan*/  ctl_ev_data ;
struct TYPE_2__ {int data_length; struct kev_msg* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_CTL_SUBCLASS ; 
 int /*<<< orphan*/  KEV_SYSTEM_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  kev_post_msg (struct kev_msg*) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_post_msg(u_int32_t event_code, u_int32_t id)
{
	struct ctl_event_data  	ctl_ev_data;
	struct kev_msg  		ev_msg;

	lck_mtx_assert(ctl_mtx, LCK_MTX_ASSERT_NOTOWNED);

	bzero(&ev_msg, sizeof(struct kev_msg));
	ev_msg.vendor_code = KEV_VENDOR_APPLE;

	ev_msg.kev_class = KEV_SYSTEM_CLASS;
	ev_msg.kev_subclass = KEV_CTL_SUBCLASS;
	ev_msg.event_code = event_code;

	/* common nke subclass data */
	bzero(&ctl_ev_data, sizeof(ctl_ev_data));
	ctl_ev_data.ctl_id = id;
	ev_msg.dv[0].data_ptr = &ctl_ev_data;
	ev_msg.dv[0].data_length = sizeof(ctl_ev_data);

	ev_msg.dv[1].data_length = 0;

	kev_post_msg(&ev_msg);
}