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
typedef  int /*<<< orphan*/  u_int32_t ;
struct kev_msg {int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_FIREWALL_CLASS ; 
 int /*<<< orphan*/  KEV_IP6FW_SUBCLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  kev_post_msg (struct kev_msg*) ; 

__attribute__((used)) static void
ip6fw_kev_post_msg(u_int32_t event_code)
{
	struct kev_msg		ev_msg;

	bzero(&ev_msg, sizeof(struct kev_msg));
	
	ev_msg.vendor_code = KEV_VENDOR_APPLE;
	ev_msg.kev_class = KEV_FIREWALL_CLASS;
	ev_msg.kev_subclass = KEV_IP6FW_SUBCLASS;
	ev_msg.event_code = event_code;

	kev_post_msg(&ev_msg);

}