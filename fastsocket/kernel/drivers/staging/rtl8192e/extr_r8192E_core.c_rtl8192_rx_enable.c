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
struct r8192_priv {int /*<<< orphan*/  rx_ring_dma; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDQDA ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8192_rx_enable(struct net_device *dev)
{
    struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
    write_nic_dword(dev, RDQDA,priv->rx_ring_dma);
}