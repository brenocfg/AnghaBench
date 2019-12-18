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
struct il_scanresults_notification {int /*<<< orphan*/  tsf_low; int /*<<< orphan*/ * stats; int /*<<< orphan*/  tsf_high; scalar_t__ band; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {scalar_t__ raw; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {scalar_t__ scan_start_tsf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il_hdl_scan_results(struct il_priv *il, struct il_rx_buf *rxb)
{
#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_scanresults_notification *notif =
	    (struct il_scanresults_notification *)pkt->u.raw;

	D_SCAN("Scan ch.res: " "%d [802.11%s] " "(TSF: 0x%08X:%08X) - %d "
	       "elapsed=%lu usec\n", notif->channel, notif->band ? "bg" : "a",
	       le32_to_cpu(notif->tsf_high), le32_to_cpu(notif->tsf_low),
	       le32_to_cpu(notif->stats[0]),
	       le32_to_cpu(notif->tsf_low) - il->scan_start_tsf);
#endif
}