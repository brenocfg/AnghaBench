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
typedef  int u64 ;
struct vnet_port {TYPE_1__* vp; } ;
struct TYPE_4__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
struct vio_net_attr_info {int addr; scalar_t__ mtu; scalar_t__ ack_freq; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  xfer_mode; TYPE_2__ tag; } ;
struct vio_driver_state {int dummy; } ;
struct net_device {scalar_t__* dev_addr; } ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_ATTR_INFO ; 
 int /*<<< orphan*/  VIO_DRING_MODE ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  VNET_ADDR_ETHERMAC ; 
 int /*<<< orphan*/  memset (struct vio_net_attr_info*,int /*<<< orphan*/ ,int) ; 
 struct vnet_port* to_vnet_port (struct vio_driver_state*) ; 
 int vio_ldc_send (struct vio_driver_state*,struct vio_net_attr_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,scalar_t__,unsigned long long) ; 

__attribute__((used)) static int vnet_send_attr(struct vio_driver_state *vio)
{
	struct vnet_port *port = to_vnet_port(vio);
	struct net_device *dev = port->vp->dev;
	struct vio_net_attr_info pkt;
	int i;

	memset(&pkt, 0, sizeof(pkt));
	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.stype = VIO_SUBTYPE_INFO;
	pkt.tag.stype_env = VIO_ATTR_INFO;
	pkt.tag.sid = vio_send_sid(vio);
	pkt.xfer_mode = VIO_DRING_MODE;
	pkt.addr_type = VNET_ADDR_ETHERMAC;
	pkt.ack_freq = 0;
	for (i = 0; i < 6; i++)
		pkt.addr |= (u64)dev->dev_addr[i] << ((5 - i) * 8);
	pkt.mtu = ETH_FRAME_LEN;

	viodbg(HS, "SEND NET ATTR xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] mtu[%llu]\n",
	       pkt.xfer_mode, pkt.addr_type,
	       (unsigned long long) pkt.addr,
	       pkt.ack_freq,
	       (unsigned long long) pkt.mtu);

	return vio_ldc_send(vio, &pkt, sizeof(pkt));
}