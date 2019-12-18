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
struct TYPE_3__ {int /*<<< orphan*/  pfxlen; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ a6; } ;
struct qeth_ipaddr {int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct qeth_card {int /*<<< orphan*/  vlangrp; } ;
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; struct inet6_ifaddr* lst_next; } ;
struct inet6_dev {struct inet6_ifaddr* addr_list; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_IP_TYPE_NORMAL ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  TRACE ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qeth_l3_delete_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_group_get_device (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void qeth_l3_free_vlan_addresses6(struct qeth_card *card,
			unsigned short vid)
{
#ifdef CONFIG_QETH_IPV6
	struct inet6_dev *in6_dev;
	struct inet6_ifaddr *ifa;
	struct qeth_ipaddr *addr;

	QETH_DBF_TEXT(TRACE, 4, "frvaddr6");

	in6_dev = in6_dev_get(vlan_group_get_device(card->vlangrp, vid));
	if (!in6_dev)
		return;
	for (ifa = in6_dev->addr_list; ifa; ifa = ifa->lst_next) {
		addr = qeth_l3_get_addr_buffer(QETH_PROT_IPV6);
		if (addr) {
			memcpy(&addr->u.a6.addr, &ifa->addr,
			       sizeof(struct in6_addr));
			addr->u.a6.pfxlen = ifa->prefix_len;
			addr->type = QETH_IP_TYPE_NORMAL;
			if (!qeth_l3_delete_ip(card, addr))
				kfree(addr);
		}
	}
	in6_dev_put(in6_dev);
#endif /* CONFIG_QETH_IPV6 */
}