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
struct sock {int dummy; } ;
struct packet_sock {struct packet_mclist* mclist; } ;
struct packet_mclist {int /*<<< orphan*/  ifindex; struct packet_mclist* next; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct packet_mclist*) ; 
 int /*<<< orphan*/  packet_dev_mc (struct net_device*,struct packet_mclist*,int) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static void packet_flush_mclist(struct sock *sk)
{
	struct packet_sock *po = pkt_sk(sk);
	struct packet_mclist *ml;

	if (!po->mclist)
		return;

	rtnl_lock();
	while ((ml = po->mclist) != NULL) {
		struct net_device *dev;

		po->mclist = ml->next;
		dev = dev_get_by_index(sock_net(sk), ml->ifindex);
		if (dev != NULL) {
			packet_dev_mc(dev, ml, -1);
			dev_put(dev);
		}
		kfree(ml);
	}
	rtnl_unlock();
}