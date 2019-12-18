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
struct net_device {scalar_t__ mtu; } ;
struct c2_rxp_hdr {int dummy; } ;
struct c2_port {scalar_t__ rx_buf_size; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ RX_BUF_SIZE ; 

__attribute__((used)) static void c2_set_rxbufsize(struct c2_port *c2_port)
{
	struct net_device *netdev = c2_port->netdev;

	if (netdev->mtu > RX_BUF_SIZE)
		c2_port->rx_buf_size =
		    netdev->mtu + ETH_HLEN + sizeof(struct c2_rxp_hdr) +
		    NET_IP_ALIGN;
	else
		c2_port->rx_buf_size = sizeof(struct c2_rxp_hdr) + RX_BUF_SIZE;
}