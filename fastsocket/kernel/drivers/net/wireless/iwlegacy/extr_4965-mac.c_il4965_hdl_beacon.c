#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {scalar_t__ raw; } ;
struct il_rx_pkt {TYPE_2__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int ibss_manager; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  failure_frame; TYPE_1__ u; int /*<<< orphan*/  rate_n_flags; } ;
struct il4965_beacon_notif {int /*<<< orphan*/  ibss_mgr_status; int /*<<< orphan*/  low_tsf; int /*<<< orphan*/  high_tsf; TYPE_3__ beacon_notify_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int TX_STATUS_MSK ; 
 int /*<<< orphan*/  il4965_hw_get_rate (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il4965_hdl_beacon(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il4965_beacon_notif *beacon =
	    (struct il4965_beacon_notif *)pkt->u.raw;
#ifdef CONFIG_IWLEGACY_DEBUG
	u8 rate = il4965_hw_get_rate(beacon->beacon_notify_hdr.rate_n_flags);

	D_RX("beacon status %x retries %d iss %d tsf:0x%.8x%.8x rate %d\n",
	     le32_to_cpu(beacon->beacon_notify_hdr.u.status) & TX_STATUS_MSK,
	     beacon->beacon_notify_hdr.failure_frame,
	     le32_to_cpu(beacon->ibss_mgr_status),
	     le32_to_cpu(beacon->high_tsf), le32_to_cpu(beacon->low_tsf), rate);
#endif
	il->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);
}