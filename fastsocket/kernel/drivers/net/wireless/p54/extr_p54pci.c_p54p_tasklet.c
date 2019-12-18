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
struct p54p_ring_control {int /*<<< orphan*/  rx_data; int /*<<< orphan*/  rx_mgmt; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  tx_mgmt; } ;
struct p54p_priv {int /*<<< orphan*/  rx_buf_data; int /*<<< orphan*/  rx_idx_data; int /*<<< orphan*/  rx_buf_mgmt; int /*<<< orphan*/  rx_idx_mgmt; int /*<<< orphan*/  tx_buf_data; int /*<<< orphan*/  tx_idx_data; int /*<<< orphan*/  tx_buf_mgmt; int /*<<< orphan*/  tx_idx_mgmt; struct p54p_ring_control* ring_control; } ;
struct ieee80211_hw {struct p54p_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISL38XX_DEV_INT_UPDATE ; 
 int /*<<< orphan*/  P54P_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_int ; 
 int /*<<< orphan*/  p54p_check_rx_ring (struct ieee80211_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54p_check_tx_ring (struct ieee80211_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void p54p_tasklet(unsigned long dev_id)
{
	struct ieee80211_hw *dev = (struct ieee80211_hw *)dev_id;
	struct p54p_priv *priv = dev->priv;
	struct p54p_ring_control *ring_control = priv->ring_control;

	p54p_check_tx_ring(dev, &priv->tx_idx_mgmt, 3, ring_control->tx_mgmt,
			   ARRAY_SIZE(ring_control->tx_mgmt),
			   priv->tx_buf_mgmt);

	p54p_check_tx_ring(dev, &priv->tx_idx_data, 1, ring_control->tx_data,
			   ARRAY_SIZE(ring_control->tx_data),
			   priv->tx_buf_data);

	p54p_check_rx_ring(dev, &priv->rx_idx_mgmt, 2, ring_control->rx_mgmt,
		ARRAY_SIZE(ring_control->rx_mgmt), priv->rx_buf_mgmt);

	p54p_check_rx_ring(dev, &priv->rx_idx_data, 0, ring_control->rx_data,
		ARRAY_SIZE(ring_control->rx_data), priv->rx_buf_data);

	wmb();
	P54P_WRITE(dev_int, cpu_to_le32(ISL38XX_DEV_INT_UPDATE));
}