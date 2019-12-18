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
struct r8192_priv {int /*<<< orphan*/ * tx_pending; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int MAX_TX_URB ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

short check_nic_enough_desc(struct net_device *dev,int queue_index)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	int used = atomic_read(&priv->tx_pending[queue_index]);

	return (used < MAX_TX_URB);
}