#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_link_report_data {int /*<<< orphan*/  line_speed; scalar_t__ link_report_flags; } ;
struct TYPE_3__ {scalar_t__ link_report_flags; } ;
struct bnx2x {int /*<<< orphan*/  dev; TYPE_1__ last_reported_link; int /*<<< orphan*/  link_cnt; } ;
typedef  int /*<<< orphan*/  cur_data ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_LINK_REPORT_FD ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_LINK_DOWN ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_RX_FC_ON ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_TX_FC_ON ; 
 int /*<<< orphan*/  CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_fill_report_data (struct bnx2x*,struct bnx2x_link_report_data*) ; 
 int /*<<< orphan*/  bnx2x_read_mf_cfg (struct bnx2x*) ; 
 int /*<<< orphan*/  memcmp (struct bnx2x_link_report_data*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct bnx2x_link_report_data*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

void __bnx2x_link_report(struct bnx2x *bp)
{
	struct bnx2x_link_report_data cur_data;

	/* reread mf_cfg */
	if (IS_PF(bp) && !CHIP_IS_E1(bp))
		bnx2x_read_mf_cfg(bp);

	/* Read the current link report info */
	bnx2x_fill_report_data(bp, &cur_data);

	/* Don't report link down or exactly the same link status twice */
	if (!memcmp(&cur_data, &bp->last_reported_link, sizeof(cur_data)) ||
	    (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		      &bp->last_reported_link.link_report_flags) &&
	     test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		      &cur_data.link_report_flags)))
		return;

	bp->link_cnt++;

	/* We are going to report a new link parameters now -
	 * remember the current data for the next time.
	 */
	memcpy(&bp->last_reported_link, &cur_data, sizeof(cur_data));

	if (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		     &cur_data.link_report_flags)) {
		netif_carrier_off(bp->dev);
		netdev_err(bp->dev, "NIC Link is Down\n");
		return;
	} else {
		const char *duplex;
		const char *flow;

		netif_carrier_on(bp->dev);

		if (test_and_clear_bit(BNX2X_LINK_REPORT_FD,
				       &cur_data.link_report_flags))
			duplex = "full";
		else
			duplex = "half";

		/* Handle the FC at the end so that only these flags would be
		 * possibly set. This way we may easily check if there is no FC
		 * enabled.
		 */
		if (cur_data.link_report_flags) {
			if (test_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				     &cur_data.link_report_flags)) {
				if (test_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				     &cur_data.link_report_flags))
					flow = "ON - receive & transmit";
				else
					flow = "ON - receive";
			} else {
				flow = "ON - transmit";
			}
		} else {
			flow = "none";
		}
		netdev_info(bp->dev, "NIC Link is Up, %d Mbps %s duplex, Flow control: %s\n",
			    cur_data.line_speed, duplex, flow);
	}
}