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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {scalar_t__ missed_beacon_threshold; int /*<<< orphan*/  status; } ;
struct iwl_missed_beacon_notif {int /*<<< orphan*/  num_expected_beacons; int /*<<< orphan*/  num_recvd_beacons; int /*<<< orphan*/  total_missed_becons; int /*<<< orphan*/  consecutive_missed_beacons; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  iwl_init_sensitivity (struct iwl_priv*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_rx_missed_beacon_notif(struct iwl_priv *priv,
				       struct iwl_rx_cmd_buffer *rxb,
				       struct iwl_device_cmd *cmd)

{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_missed_beacon_notif *missed_beacon = (void *)pkt->data;

	if (le32_to_cpu(missed_beacon->consecutive_missed_beacons) >
	    priv->missed_beacon_threshold) {
		IWL_DEBUG_CALIB(priv,
		    "missed bcn cnsq %d totl %d rcd %d expctd %d\n",
		    le32_to_cpu(missed_beacon->consecutive_missed_beacons),
		    le32_to_cpu(missed_beacon->total_missed_becons),
		    le32_to_cpu(missed_beacon->num_recvd_beacons),
		    le32_to_cpu(missed_beacon->num_expected_beacons));
		if (!test_bit(STATUS_SCANNING, &priv->status))
			iwl_init_sensitivity(priv);
	}
	return 0;
}