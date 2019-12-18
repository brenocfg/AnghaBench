#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ a4; } ;
struct qeth_ipaddr {int /*<<< orphan*/  type; TYPE_3__ u; } ;
struct qeth_card {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_mask; int /*<<< orphan*/  ifa_address; TYPE_1__* ifa_dev; } ;
struct TYPE_4__ {scalar_t__ dev; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_IP_TYPE_NORMAL ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_add_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_delete_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int /*<<< orphan*/ ) ; 
 struct qeth_card* qeth_l3_get_card_from_dev (struct net_device*) ; 
 int /*<<< orphan*/  qeth_l3_set_ip_addr_list (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l3_ip_event(struct notifier_block *this,
			    unsigned long event, void *ptr)
{
	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct net_device *dev = (struct net_device *)ifa->ifa_dev->dev;
	struct qeth_ipaddr *addr;
	struct qeth_card *card;

	if (dev_net(dev) != &init_net)
		return NOTIFY_DONE;

	QETH_DBF_TEXT(TRACE, 3, "ipevent");
	card = qeth_l3_get_card_from_dev(dev);
	if (!card)
		return NOTIFY_DONE;

	addr = qeth_l3_get_addr_buffer(QETH_PROT_IPV4);
	if (addr != NULL) {
		addr->u.a4.addr = ifa->ifa_address;
		addr->u.a4.mask = ifa->ifa_mask;
		addr->type = QETH_IP_TYPE_NORMAL;
	} else
		goto out;

	switch (event) {
	case NETDEV_UP:
		if (!qeth_l3_add_ip(card, addr))
			kfree(addr);
		break;
	case NETDEV_DOWN:
		if (!qeth_l3_delete_ip(card, addr))
			kfree(addr);
		break;
	default:
		break;
	}
	qeth_l3_set_ip_addr_list(card);
out:
	return NOTIFY_DONE;
}