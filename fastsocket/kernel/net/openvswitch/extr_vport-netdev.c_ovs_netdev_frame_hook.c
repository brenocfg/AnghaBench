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
struct vport {int dummy; } ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PACKET_LOOPBACK ; 
 int /*<<< orphan*/  netdev_port_receive (struct vport*,struct sk_buff*) ; 
 struct vport* ovs_netdev_get_vport (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *ovs_netdev_frame_hook(struct sk_buff *skb)
{
	struct vport *vport;

	if (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		return skb;

	vport = ovs_netdev_get_vport(skb->dev);

	netdev_port_receive(vport, skb);

	return NULL;
}