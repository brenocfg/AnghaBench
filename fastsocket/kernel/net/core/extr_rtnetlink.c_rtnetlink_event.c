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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int IFF_RUNNING ; 
 unsigned int IFF_UP ; 
#define  NETDEV_CHANGE 136 
#define  NETDEV_DOWN 135 
#define  NETDEV_GOING_DOWN 134 
#define  NETDEV_JOIN 133 
#define  NETDEV_POST_INIT 132 
#define  NETDEV_REGISTER 131 
#define  NETDEV_RELEASE 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  rtmsg_ifinfo (int /*<<< orphan*/ ,struct net_device*,unsigned int) ; 

__attribute__((used)) static int rtnetlink_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;

	switch (event) {
	case NETDEV_UNREGISTER:
		rtmsg_ifinfo(RTM_DELLINK, dev, ~0U);
		break;
	case NETDEV_UP:
	case NETDEV_DOWN:
		rtmsg_ifinfo(RTM_NEWLINK, dev, IFF_UP|IFF_RUNNING);
		break;
	case NETDEV_POST_INIT:
	case NETDEV_REGISTER:
	case NETDEV_CHANGE:
	case NETDEV_GOING_DOWN:
	case NETDEV_RELEASE:
	case NETDEV_JOIN:
		break;
	default:
		rtmsg_ifinfo(RTM_NEWLINK, dev, 0);
		break;
	}
	return NOTIFY_DONE;
}