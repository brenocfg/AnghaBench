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
typedef  int /*<<< orphan*/  u8 ;
struct qib_verbs_counters {int /*<<< orphan*/  port_rcv_packets; int /*<<< orphan*/  port_xmit_packets; int /*<<< orphan*/  port_rcv_data; int /*<<< orphan*/  port_xmit_data; int /*<<< orphan*/  vl15_dropped; int /*<<< orphan*/  excessive_buffer_overrun_errors; int /*<<< orphan*/  local_link_integrity_errors; int /*<<< orphan*/  port_xmit_discards; int /*<<< orphan*/  port_rcv_remphys_errors; int /*<<< orphan*/  port_rcv_errors; int /*<<< orphan*/  link_downed_counter; int /*<<< orphan*/  link_error_recovery_counter; int /*<<< orphan*/  symbol_error_counter; } ;
struct qib_pportdata {int dummy; } ;
struct qib_ibport {int /*<<< orphan*/  z_port_rcv_packets; int /*<<< orphan*/  z_port_xmit_packets; int /*<<< orphan*/  z_port_rcv_data; int /*<<< orphan*/  z_port_xmit_data; int /*<<< orphan*/  z_vl15_dropped; scalar_t__ n_vl15_dropped; int /*<<< orphan*/  z_excessive_buffer_overrun_errors; int /*<<< orphan*/  z_local_link_integrity_errors; int /*<<< orphan*/  z_port_xmit_discards; int /*<<< orphan*/  z_port_rcv_remphys_errors; int /*<<< orphan*/  z_port_rcv_errors; int /*<<< orphan*/  z_link_downed_counter; int /*<<< orphan*/  z_link_error_recovery_counter; int /*<<< orphan*/  z_symbol_error_counter; } ;
struct ib_pma_portcounters {int counter_select; } ;
struct ib_pma_mad {scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_PMA_SEL_EXCESSIVE_BUFFER_OVERRUNS ; 
 int IB_PMA_SEL_LINK_DOWNED ; 
 int IB_PMA_SEL_LINK_ERROR_RECOVERY ; 
 int IB_PMA_SEL_LOCAL_LINK_INTEGRITY_ERRORS ; 
 int IB_PMA_SEL_PORT_RCV_DATA ; 
 int IB_PMA_SEL_PORT_RCV_ERRORS ; 
 int IB_PMA_SEL_PORT_RCV_PACKETS ; 
 int IB_PMA_SEL_PORT_RCV_REMPHYS_ERRORS ; 
 int IB_PMA_SEL_PORT_VL15_DROPPED ; 
 int IB_PMA_SEL_PORT_XMIT_DATA ; 
 int IB_PMA_SEL_PORT_XMIT_DISCARDS ; 
 int IB_PMA_SEL_PORT_XMIT_PACKETS ; 
 int IB_PMA_SEL_SYMBOL_ERROR ; 
 int pma_get_portcounters (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_get_counters (struct qib_pportdata*,struct qib_verbs_counters*) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pma_set_portcounters(struct ib_pma_mad *pmp,
				struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portcounters *p = (struct ib_pma_portcounters *)
		pmp->data;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_verbs_counters cntrs;

	/*
	 * Since the HW doesn't support clearing counters, we save the
	 * current count and subtract it from future responses.
	 */
	qib_get_counters(ppd, &cntrs);

	if (p->counter_select & IB_PMA_SEL_SYMBOL_ERROR)
		ibp->z_symbol_error_counter = cntrs.symbol_error_counter;

	if (p->counter_select & IB_PMA_SEL_LINK_ERROR_RECOVERY)
		ibp->z_link_error_recovery_counter =
			cntrs.link_error_recovery_counter;

	if (p->counter_select & IB_PMA_SEL_LINK_DOWNED)
		ibp->z_link_downed_counter = cntrs.link_downed_counter;

	if (p->counter_select & IB_PMA_SEL_PORT_RCV_ERRORS)
		ibp->z_port_rcv_errors = cntrs.port_rcv_errors;

	if (p->counter_select & IB_PMA_SEL_PORT_RCV_REMPHYS_ERRORS)
		ibp->z_port_rcv_remphys_errors =
			cntrs.port_rcv_remphys_errors;

	if (p->counter_select & IB_PMA_SEL_PORT_XMIT_DISCARDS)
		ibp->z_port_xmit_discards = cntrs.port_xmit_discards;

	if (p->counter_select & IB_PMA_SEL_LOCAL_LINK_INTEGRITY_ERRORS)
		ibp->z_local_link_integrity_errors =
			cntrs.local_link_integrity_errors;

	if (p->counter_select & IB_PMA_SEL_EXCESSIVE_BUFFER_OVERRUNS)
		ibp->z_excessive_buffer_overrun_errors =
			cntrs.excessive_buffer_overrun_errors;

	if (p->counter_select & IB_PMA_SEL_PORT_VL15_DROPPED) {
		ibp->n_vl15_dropped = 0;
		ibp->z_vl15_dropped = cntrs.vl15_dropped;
	}

	if (p->counter_select & IB_PMA_SEL_PORT_XMIT_DATA)
		ibp->z_port_xmit_data = cntrs.port_xmit_data;

	if (p->counter_select & IB_PMA_SEL_PORT_RCV_DATA)
		ibp->z_port_rcv_data = cntrs.port_rcv_data;

	if (p->counter_select & IB_PMA_SEL_PORT_XMIT_PACKETS)
		ibp->z_port_xmit_packets = cntrs.port_xmit_packets;

	if (p->counter_select & IB_PMA_SEL_PORT_RCV_PACKETS)
		ibp->z_port_rcv_packets = cntrs.port_rcv_packets;

	return pma_get_portcounters(pmp, ibdev, port);
}