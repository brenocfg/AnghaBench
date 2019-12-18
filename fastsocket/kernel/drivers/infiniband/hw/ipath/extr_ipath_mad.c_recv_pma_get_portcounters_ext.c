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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ipath_ibdev {int /*<<< orphan*/  n_multicast_rcv; int /*<<< orphan*/  n_multicast_xmit; int /*<<< orphan*/  n_unicast_rcv; int /*<<< orphan*/  n_unicast_xmit; scalar_t__ z_port_rcv_packets; scalar_t__ z_port_xmit_packets; scalar_t__ z_port_rcv_data; scalar_t__ z_port_xmit_data; int /*<<< orphan*/  dd; } ;
struct ib_smp {int dummy; } ;
struct ib_pma_portcounters_ext {int port_select; void* port_multicast_rcv_packets; void* port_multicast_xmit_packets; void* port_unicast_rcv_packets; void* port_unicast_xmit_packets; void* port_rcv_packets; void* port_xmit_packets; void* port_rcv_data; void* port_xmit_data; } ;
struct TYPE_2__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_snapshot_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int recv_pma_get_portcounters_ext(struct ib_pma_mad *pmp,
					 struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portcounters_ext *p =
		(struct ib_pma_portcounters_ext *)pmp->data;
	struct ipath_ibdev *dev = to_idev(ibdev);
	u64 swords, rwords, spkts, rpkts, xwait;
	u8 port_select = p->port_select;

	ipath_snapshot_counters(dev->dd, &swords, &rwords, &spkts,
				&rpkts, &xwait);

	/* Adjust counters for any resets done. */
	swords -= dev->z_port_xmit_data;
	rwords -= dev->z_port_rcv_data;
	spkts -= dev->z_port_xmit_packets;
	rpkts -= dev->z_port_rcv_packets;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->port_select = port_select;
	if (pmp->mad_hdr.attr_mod != 0 ||
	    (port_select != port && port_select != 0xFF))
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	p->port_xmit_data = cpu_to_be64(swords);
	p->port_rcv_data = cpu_to_be64(rwords);
	p->port_xmit_packets = cpu_to_be64(spkts);
	p->port_rcv_packets = cpu_to_be64(rpkts);
	p->port_unicast_xmit_packets = cpu_to_be64(dev->n_unicast_xmit);
	p->port_unicast_rcv_packets = cpu_to_be64(dev->n_unicast_rcv);
	p->port_multicast_xmit_packets = cpu_to_be64(dev->n_multicast_xmit);
	p->port_multicast_rcv_packets = cpu_to_be64(dev->n_multicast_rcv);

	return reply((struct ib_smp *) pmp);
}