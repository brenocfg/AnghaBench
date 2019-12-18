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
struct sk_buff {int dummy; } ;
struct llc_station_state_ev {scalar_t__ type; } ;
struct llc_pdu_un {int /*<<< orphan*/  dsap; } ;
struct TYPE_2__ {int xid_r_count; } ;

/* Variables and functions */
 scalar_t__ LLC_1_PDU_CMD_XID ; 
 scalar_t__ LLC_PDU_IS_RSP (struct llc_pdu_un*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_U (struct llc_pdu_un*) ; 
 scalar_t__ LLC_STATION_EV_TYPE_PDU ; 
 scalar_t__ LLC_U_PDU_RSP (struct llc_pdu_un*) ; 
 TYPE_1__ llc_main_station ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 
 struct llc_station_state_ev* llc_station_ev (struct sk_buff*) ; 

__attribute__((used)) static int llc_stat_ev_rx_null_dsap_1_xid_r_xid_r_cnt_eq(struct sk_buff *skb)
{
	struct llc_station_state_ev *ev = llc_station_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_STATION_EV_TYPE_PDU &&
	       LLC_PDU_IS_RSP(pdu) &&			/* response PDU */
	       LLC_PDU_TYPE_IS_U(pdu) &&		/* U type PDU */
	       LLC_U_PDU_RSP(pdu) == LLC_1_PDU_CMD_XID &&
	       !pdu->dsap &&				/* NULL DSAP value */
	       llc_main_station.xid_r_count == 1 ? 0 : 1;
}