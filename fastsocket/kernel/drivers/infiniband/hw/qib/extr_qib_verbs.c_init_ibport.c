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
struct qib_verbs_counters {int /*<<< orphan*/  vl15_dropped; int /*<<< orphan*/  excessive_buffer_overrun_errors; int /*<<< orphan*/  local_link_integrity_errors; int /*<<< orphan*/  port_rcv_packets; int /*<<< orphan*/  port_xmit_packets; int /*<<< orphan*/  port_rcv_data; int /*<<< orphan*/  port_xmit_data; int /*<<< orphan*/  port_xmit_discards; int /*<<< orphan*/  port_rcv_remphys_errors; int /*<<< orphan*/  port_rcv_errors; int /*<<< orphan*/  link_downed_counter; int /*<<< orphan*/  link_error_recovery_counter; int /*<<< orphan*/  symbol_error_counter; } ;
struct qib_ibport {int port_cap_flags; int /*<<< orphan*/  qp1; int /*<<< orphan*/  qp0; int /*<<< orphan*/  z_vl15_dropped; int /*<<< orphan*/  z_excessive_buffer_overrun_errors; int /*<<< orphan*/  z_local_link_integrity_errors; int /*<<< orphan*/  z_port_rcv_packets; int /*<<< orphan*/  z_port_xmit_packets; int /*<<< orphan*/  z_port_rcv_data; int /*<<< orphan*/  z_port_xmit_data; int /*<<< orphan*/  z_port_xmit_discards; int /*<<< orphan*/  z_port_rcv_remphys_errors; int /*<<< orphan*/  z_port_rcv_errors; int /*<<< orphan*/  z_link_downed_counter; int /*<<< orphan*/  z_link_error_recovery_counter; int /*<<< orphan*/  z_symbol_error_counter; int /*<<< orphan*/ * pma_counter_select; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  gid_prefix; int /*<<< orphan*/  lock; } ;
struct qib_pportdata {TYPE_1__* dd; struct qib_ibport ibport_data; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_DEFAULT_GID_PREFIX ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int /*<<< orphan*/  IB_PMA_PORT_RCV_DATA ; 
 int /*<<< orphan*/  IB_PMA_PORT_RCV_PKTS ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_DATA ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_PKTS ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_WAIT ; 
 int IB_PORT_AUTO_MIGR_SUP ; 
 int IB_PORT_CAP_MASK_NOTICE_SUP ; 
 int IB_PORT_CLIENT_REG_SUP ; 
 int IB_PORT_DR_NOTICE_SUP ; 
 int IB_PORT_LINK_LATENCY_SUP ; 
 int IB_PORT_OTHER_LOCAL_CHANGES_SUP ; 
 int IB_PORT_SL_MAP_SUP ; 
 int IB_PORT_SYS_IMAGE_GUID_SUP ; 
 int IB_PORT_TRAP_SUP ; 
 int QIB_HAS_LINK_LATENCY ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_get_counters (struct qib_pportdata*,struct qib_verbs_counters*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_ibport(struct qib_pportdata *ppd)
{
	struct qib_verbs_counters cntrs;
	struct qib_ibport *ibp = &ppd->ibport_data;

	spin_lock_init(&ibp->lock);
	/* Set the prefix to the default value (see ch. 4.1.1) */
	ibp->gid_prefix = IB_DEFAULT_GID_PREFIX;
	ibp->sm_lid = be16_to_cpu(IB_LID_PERMISSIVE);
	ibp->port_cap_flags = IB_PORT_SYS_IMAGE_GUID_SUP |
		IB_PORT_CLIENT_REG_SUP | IB_PORT_SL_MAP_SUP |
		IB_PORT_TRAP_SUP | IB_PORT_AUTO_MIGR_SUP |
		IB_PORT_DR_NOTICE_SUP | IB_PORT_CAP_MASK_NOTICE_SUP |
		IB_PORT_OTHER_LOCAL_CHANGES_SUP;
	if (ppd->dd->flags & QIB_HAS_LINK_LATENCY)
		ibp->port_cap_flags |= IB_PORT_LINK_LATENCY_SUP;
	ibp->pma_counter_select[0] = IB_PMA_PORT_XMIT_DATA;
	ibp->pma_counter_select[1] = IB_PMA_PORT_RCV_DATA;
	ibp->pma_counter_select[2] = IB_PMA_PORT_XMIT_PKTS;
	ibp->pma_counter_select[3] = IB_PMA_PORT_RCV_PKTS;
	ibp->pma_counter_select[4] = IB_PMA_PORT_XMIT_WAIT;

	/* Snapshot current HW counters to "clear" them. */
	qib_get_counters(ppd, &cntrs);
	ibp->z_symbol_error_counter = cntrs.symbol_error_counter;
	ibp->z_link_error_recovery_counter =
		cntrs.link_error_recovery_counter;
	ibp->z_link_downed_counter = cntrs.link_downed_counter;
	ibp->z_port_rcv_errors = cntrs.port_rcv_errors;
	ibp->z_port_rcv_remphys_errors = cntrs.port_rcv_remphys_errors;
	ibp->z_port_xmit_discards = cntrs.port_xmit_discards;
	ibp->z_port_xmit_data = cntrs.port_xmit_data;
	ibp->z_port_rcv_data = cntrs.port_rcv_data;
	ibp->z_port_xmit_packets = cntrs.port_xmit_packets;
	ibp->z_port_rcv_packets = cntrs.port_rcv_packets;
	ibp->z_local_link_integrity_errors =
		cntrs.local_link_integrity_errors;
	ibp->z_excessive_buffer_overrun_errors =
		cntrs.excessive_buffer_overrun_errors;
	ibp->z_vl15_dropped = cntrs.vl15_dropped;
	rcu_assign_pointer(ibp->qp0, NULL);
	rcu_assign_pointer(ibp->qp1, NULL);
}