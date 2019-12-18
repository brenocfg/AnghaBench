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
typedef  int u32 ;
typedef  int u16 ;
struct ipath_verbs_counters {int symbol_error_counter; int link_error_recovery_counter; int link_downed_counter; int port_rcv_errors; int port_rcv_remphys_errors; int port_xmit_discards; int port_xmit_data; int port_rcv_data; int port_xmit_packets; int port_rcv_packets; int local_link_integrity_errors; int excessive_buffer_overrun_errors; int vl15_dropped; } ;
struct ipath_ibdev {scalar_t__ n_vl15_dropped; scalar_t__ z_vl15_dropped; scalar_t__ z_excessive_buffer_overrun_errors; scalar_t__ z_local_link_integrity_errors; scalar_t__ z_port_rcv_packets; scalar_t__ z_port_xmit_packets; scalar_t__ z_port_rcv_data; scalar_t__ z_port_xmit_data; scalar_t__ z_port_xmit_discards; scalar_t__ z_port_rcv_remphys_errors; scalar_t__ z_port_rcv_errors; scalar_t__ rcv_errors; scalar_t__ z_link_downed_counter; scalar_t__ z_link_error_recovery_counter; scalar_t__ z_symbol_error_counter; int /*<<< orphan*/  dd; } ;
struct ib_smp {int dummy; } ;
struct ib_pma_portcounters {int port_select; int link_error_recovery_counter; int link_downed_counter; int link_overrun_errors; void* port_rcv_packets; void* port_xmit_packets; void* port_rcv_data; void* port_xmit_data; void* vl15_dropped; void* port_xmit_discards; void* port_rcv_remphys_errors; void* port_rcv_errors; void* symbol_error_counter; } ;
struct TYPE_2__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  ipath_get_counters (int /*<<< orphan*/ ,struct ipath_verbs_counters*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int recv_pma_get_portcounters(struct ib_pma_mad *pmp,
				     struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portcounters *p = (struct ib_pma_portcounters *)
		pmp->data;
	struct ipath_ibdev *dev = to_idev(ibdev);
	struct ipath_verbs_counters cntrs;
	u8 port_select = p->port_select;

	ipath_get_counters(dev->dd, &cntrs);

	/* Adjust counters for any resets done. */
	cntrs.symbol_error_counter -= dev->z_symbol_error_counter;
	cntrs.link_error_recovery_counter -=
		dev->z_link_error_recovery_counter;
	cntrs.link_downed_counter -= dev->z_link_downed_counter;
	cntrs.port_rcv_errors += dev->rcv_errors;
	cntrs.port_rcv_errors -= dev->z_port_rcv_errors;
	cntrs.port_rcv_remphys_errors -= dev->z_port_rcv_remphys_errors;
	cntrs.port_xmit_discards -= dev->z_port_xmit_discards;
	cntrs.port_xmit_data -= dev->z_port_xmit_data;
	cntrs.port_rcv_data -= dev->z_port_rcv_data;
	cntrs.port_xmit_packets -= dev->z_port_xmit_packets;
	cntrs.port_rcv_packets -= dev->z_port_rcv_packets;
	cntrs.local_link_integrity_errors -=
		dev->z_local_link_integrity_errors;
	cntrs.excessive_buffer_overrun_errors -=
		dev->z_excessive_buffer_overrun_errors;
	cntrs.vl15_dropped -= dev->z_vl15_dropped;
	cntrs.vl15_dropped += dev->n_vl15_dropped;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->port_select = port_select;
	if (pmp->mad_hdr.attr_mod != 0 ||
	    (port_select != port && port_select != 0xFF))
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	if (cntrs.symbol_error_counter > 0xFFFFUL)
		p->symbol_error_counter = cpu_to_be16(0xFFFF);
	else
		p->symbol_error_counter =
			cpu_to_be16((u16)cntrs.symbol_error_counter);
	if (cntrs.link_error_recovery_counter > 0xFFUL)
		p->link_error_recovery_counter = 0xFF;
	else
		p->link_error_recovery_counter =
			(u8)cntrs.link_error_recovery_counter;
	if (cntrs.link_downed_counter > 0xFFUL)
		p->link_downed_counter = 0xFF;
	else
		p->link_downed_counter = (u8)cntrs.link_downed_counter;
	if (cntrs.port_rcv_errors > 0xFFFFUL)
		p->port_rcv_errors = cpu_to_be16(0xFFFF);
	else
		p->port_rcv_errors =
			cpu_to_be16((u16) cntrs.port_rcv_errors);
	if (cntrs.port_rcv_remphys_errors > 0xFFFFUL)
		p->port_rcv_remphys_errors = cpu_to_be16(0xFFFF);
	else
		p->port_rcv_remphys_errors =
			cpu_to_be16((u16)cntrs.port_rcv_remphys_errors);
	if (cntrs.port_xmit_discards > 0xFFFFUL)
		p->port_xmit_discards = cpu_to_be16(0xFFFF);
	else
		p->port_xmit_discards =
			cpu_to_be16((u16)cntrs.port_xmit_discards);
	if (cntrs.local_link_integrity_errors > 0xFUL)
		cntrs.local_link_integrity_errors = 0xFUL;
	if (cntrs.excessive_buffer_overrun_errors > 0xFUL)
		cntrs.excessive_buffer_overrun_errors = 0xFUL;
	p->link_overrun_errors = (cntrs.local_link_integrity_errors << 4) |
		cntrs.excessive_buffer_overrun_errors;
	if (cntrs.vl15_dropped > 0xFFFFUL)
		p->vl15_dropped = cpu_to_be16(0xFFFF);
	else
		p->vl15_dropped = cpu_to_be16((u16)cntrs.vl15_dropped);
	if (cntrs.port_xmit_data > 0xFFFFFFFFUL)
		p->port_xmit_data = cpu_to_be32(0xFFFFFFFF);
	else
		p->port_xmit_data = cpu_to_be32((u32)cntrs.port_xmit_data);
	if (cntrs.port_rcv_data > 0xFFFFFFFFUL)
		p->port_rcv_data = cpu_to_be32(0xFFFFFFFF);
	else
		p->port_rcv_data = cpu_to_be32((u32)cntrs.port_rcv_data);
	if (cntrs.port_xmit_packets > 0xFFFFFFFFUL)
		p->port_xmit_packets = cpu_to_be32(0xFFFFFFFF);
	else
		p->port_xmit_packets =
			cpu_to_be32((u32)cntrs.port_xmit_packets);
	if (cntrs.port_rcv_packets > 0xFFFFFFFFUL)
		p->port_rcv_packets = cpu_to_be32(0xFFFFFFFF);
	else
		p->port_rcv_packets =
			cpu_to_be32((u32) cntrs.port_rcv_packets);

	return reply((struct ib_smp *) pmp);
}