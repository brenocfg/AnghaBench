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
struct sk_buff {short len; unsigned char* data; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 short ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int netwave_hw_xmit (unsigned char*,short,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t netwave_start_xmit(struct sk_buff *skb,
					    struct net_device *dev) {
	/* This flag indicate that the hardware can't perform a transmission.
	 * Theoritically, NET3 check it before sending a packet to the driver,
	 * but in fact it never do that and pool continuously.
	 * As the watchdog will abort too long transmissions, we are quite safe...
	 */

    netif_stop_queue(dev);

    {
	short length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	unsigned char* buf = skb->data;
	
	if (netwave_hw_xmit( buf, length, dev) == 1) {
	    /* Some error, let's make them call us another time? */
	    netif_start_queue(dev);
	}
	dev->trans_start = jiffies;
    }
    dev_kfree_skb(skb);
    
    return NETDEV_TX_OK;
}