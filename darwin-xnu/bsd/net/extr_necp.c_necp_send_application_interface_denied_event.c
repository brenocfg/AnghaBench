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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  euuid; int /*<<< orphan*/  epid; } ;
struct kev_netpolicy_ifdenied {TYPE_1__ ev_data; int /*<<< orphan*/  ev_if_functional_type; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ev_ifdenied ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_NETPOLICY_IFDENIED ; 
 int /*<<< orphan*/  bzero (struct kev_netpolicy_ifdenied*,int) ; 
 int /*<<< orphan*/  netpolicy_post_msg (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
necp_send_application_interface_denied_event(pid_t pid, uuid_t proc_uuid, u_int32_t if_functional_type)
{
	struct kev_netpolicy_ifdenied ev_ifdenied;

	bzero(&ev_ifdenied, sizeof(ev_ifdenied));

	ev_ifdenied.ev_data.epid = pid;
	uuid_copy(ev_ifdenied.ev_data.euuid, proc_uuid);
	ev_ifdenied.ev_if_functional_type = if_functional_type;

	netpolicy_post_msg(KEV_NETPOLICY_IFDENIED, &ev_ifdenied.ev_data, sizeof(ev_ifdenied));
}