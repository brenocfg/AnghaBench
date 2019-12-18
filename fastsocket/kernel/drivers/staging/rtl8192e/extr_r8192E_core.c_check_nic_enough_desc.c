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
struct rtl8192_tx_ring {int entries; int /*<<< orphan*/  queue; } ;
struct r8192_priv {struct rtl8192_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 

short check_nic_enough_desc(struct net_device *dev, int prio)
{
    struct r8192_priv *priv = ieee80211_priv(dev);
    struct rtl8192_tx_ring *ring = &priv->tx_ring[prio];

    /* for now we reserve two free descriptor as a safety boundary
     * between the tail and the head
     */
    if (ring->entries - skb_queue_len(&ring->queue) >= 2) {
        return 1;
    } else {
        return 0;
    }
}