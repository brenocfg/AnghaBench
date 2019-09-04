#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_3__ {int /*<<< orphan*/  netagent_domain; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;
struct TYPE_4__ {int /*<<< orphan*/  euuid; int /*<<< orphan*/  epid; } ;
struct kev_netpolicy_ifdenied {TYPE_2__ ev_data; int /*<<< orphan*/  ev_if_functional_type; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ev_ifdenied ;

/* Variables and functions */
 int /*<<< orphan*/  IFRTYPE_FUNCTIONAL_CELLULAR ; 
 int /*<<< orphan*/  KEV_NETPOLICY_IFFAILED ; 
 int /*<<< orphan*/  NETAGENT_DOMAINSIZE ; 
 int /*<<< orphan*/  bzero (struct kev_netpolicy_ifdenied*,int) ; 
 int /*<<< orphan*/  netpolicy_post_msg (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netagent_send_cellular_failed_event(struct netagent_wrapper *wrapper,
									pid_t pid, uuid_t proc_uuid)
{
	if (strncmp(wrapper->netagent.netagent_domain, "Cellular", NETAGENT_DOMAINSIZE) != 0) {
		return;
	}

	struct kev_netpolicy_ifdenied ev_ifdenied;

	bzero(&ev_ifdenied, sizeof(ev_ifdenied));

	ev_ifdenied.ev_data.epid = pid;
	uuid_copy(ev_ifdenied.ev_data.euuid, proc_uuid);
	ev_ifdenied.ev_if_functional_type = IFRTYPE_FUNCTIONAL_CELLULAR;

	netpolicy_post_msg(KEV_NETPOLICY_IFFAILED, &ev_ifdenied.ev_data, sizeof(ev_ifdenied));
}