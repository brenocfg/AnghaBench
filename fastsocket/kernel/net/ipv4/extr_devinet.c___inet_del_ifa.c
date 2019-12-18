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
typedef  int /*<<< orphan*/  u32 ;
struct nlmsghdr {int dummy; } ;
struct in_ifaddr {int ifa_flags; scalar_t__ ifa_scope; scalar_t__ ifa_mask; int /*<<< orphan*/  ifa_address; struct in_ifaddr* ifa_next; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int IFA_F_SECONDARY ; 
 int IN_DEV_PROMOTE_SECONDARIES (struct in_device*) ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in_ifaddr*) ; 
 int /*<<< orphan*/  fib_add_ifaddr (struct in_ifaddr*) ; 
 int /*<<< orphan*/  inet_free_ifa (struct in_ifaddr*) ; 
 int /*<<< orphan*/  inet_ifa_match (int /*<<< orphan*/ ,struct in_ifaddr*) ; 
 int /*<<< orphan*/  inetaddr_chain ; 
 int /*<<< orphan*/  rtmsg_ifa (int /*<<< orphan*/ ,struct in_ifaddr*,struct nlmsghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __inet_del_ifa(struct in_device *in_dev, struct in_ifaddr **ifap,
			 int destroy, struct nlmsghdr *nlh, u32 pid)
{
	struct in_ifaddr *promote = NULL;
	struct in_ifaddr *ifa, *ifa1 = *ifap;
	struct in_ifaddr *last_prim = in_dev->ifa_list;
	struct in_ifaddr *prev_prom = NULL;
	int do_promote = IN_DEV_PROMOTE_SECONDARIES(in_dev);

	ASSERT_RTNL();

	/* 1. Deleting primary ifaddr forces deletion all secondaries
	 * unless alias promotion is set
	 **/

	if (!(ifa1->ifa_flags & IFA_F_SECONDARY)) {
		struct in_ifaddr **ifap1 = &ifa1->ifa_next;

		while ((ifa = *ifap1) != NULL) {
			if (!(ifa->ifa_flags & IFA_F_SECONDARY) &&
			    ifa1->ifa_scope <= ifa->ifa_scope)
				last_prim = ifa;

			if (!(ifa->ifa_flags & IFA_F_SECONDARY) ||
			    ifa1->ifa_mask != ifa->ifa_mask ||
			    !inet_ifa_match(ifa1->ifa_address, ifa)) {
				ifap1 = &ifa->ifa_next;
				prev_prom = ifa;
				continue;
			}

			if (!do_promote) {
				*ifap1 = ifa->ifa_next;

				rtmsg_ifa(RTM_DELADDR, ifa, nlh, pid);
				blocking_notifier_call_chain(&inetaddr_chain,
						NETDEV_DOWN, ifa);
				inet_free_ifa(ifa);
			} else {
				promote = ifa;
				break;
			}
		}
	}

	/* 2. Unlink it */

	*ifap = ifa1->ifa_next;

	/* 3. Announce address deletion */

	/* Send message first, then call notifier.
	   At first sight, FIB update triggered by notifier
	   will refer to already deleted ifaddr, that could confuse
	   netlink listeners. It is not true: look, gated sees
	   that route deleted and if it still thinks that ifaddr
	   is valid, it will try to restore deleted routes... Grr.
	   So that, this order is correct.
	 */
	rtmsg_ifa(RTM_DELADDR, ifa1, nlh, pid);
	blocking_notifier_call_chain(&inetaddr_chain, NETDEV_DOWN, ifa1);

	if (promote) {

		if (prev_prom) {
			prev_prom->ifa_next = promote->ifa_next;
			promote->ifa_next = last_prim->ifa_next;
			last_prim->ifa_next = promote;
		}

		promote->ifa_flags &= ~IFA_F_SECONDARY;
		rtmsg_ifa(RTM_NEWADDR, promote, nlh, pid);
		blocking_notifier_call_chain(&inetaddr_chain,
				NETDEV_UP, promote);
		for (ifa = promote->ifa_next; ifa; ifa = ifa->ifa_next) {
			if (ifa1->ifa_mask != ifa->ifa_mask ||
			    !inet_ifa_match(ifa1->ifa_address, ifa))
					continue;
			fib_add_ifaddr(ifa);
		}

	}
	if (destroy)
		inet_free_ifa(ifa1);
}