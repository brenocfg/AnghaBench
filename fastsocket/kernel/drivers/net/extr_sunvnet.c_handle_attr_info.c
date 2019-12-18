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
struct TYPE_2__ {int /*<<< orphan*/  stype; int /*<<< orphan*/  sid; } ;
struct vio_net_attr_info {scalar_t__ xfer_mode; scalar_t__ addr_type; scalar_t__ mtu; TYPE_1__ tag; int /*<<< orphan*/  ack_freq; scalar_t__ addr; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  HS ; 
 scalar_t__ VIO_DRING_MODE ; 
 int /*<<< orphan*/  VIO_SUBTYPE_ACK ; 
 int /*<<< orphan*/  VIO_SUBTYPE_NACK ; 
 scalar_t__ VNET_ADDR_ETHERMAC ; 
 int vio_ldc_send (struct vio_driver_state*,struct vio_net_attr_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int handle_attr_info(struct vio_driver_state *vio,
			    struct vio_net_attr_info *pkt)
{
	viodbg(HS, "GOT NET ATTR INFO xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] mtu[%llu]\n",
	       pkt->xfer_mode, pkt->addr_type,
	       (unsigned long long) pkt->addr,
	       pkt->ack_freq,
	       (unsigned long long) pkt->mtu);

	pkt->tag.sid = vio_send_sid(vio);

	if (pkt->xfer_mode != VIO_DRING_MODE ||
	    pkt->addr_type != VNET_ADDR_ETHERMAC ||
	    pkt->mtu != ETH_FRAME_LEN) {
		viodbg(HS, "SEND NET ATTR NACK\n");

		pkt->tag.stype = VIO_SUBTYPE_NACK;

		(void) vio_ldc_send(vio, pkt, sizeof(*pkt));

		return -ECONNRESET;
	} else {
		viodbg(HS, "SEND NET ATTR ACK\n");

		pkt->tag.stype = VIO_SUBTYPE_ACK;

		return vio_ldc_send(vio, pkt, sizeof(*pkt));
	}

}