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
struct TYPE_2__ {int /*<<< orphan*/  last_rssi; } ;
struct ath9k_htc_priv {TYPE_1__ rx; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  OP_SCANNING ; 
 int /*<<< orphan*/  ath9k_htc_opmode_init (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_hw_rxena (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_startpcureceive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_host_rx_init(struct ath9k_htc_priv *priv)
{
	ath9k_hw_rxena(priv->ah);
	ath9k_htc_opmode_init(priv);
	ath9k_hw_startpcureceive(priv->ah, test_bit(OP_SCANNING, &priv->op_flags));
	priv->rx.last_rssi = ATH_RSSI_DUMMY_MARKER;
}