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
struct tsi108_prv_data {int rxfree; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int TSI108_RXRING_LEN ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_rx_int (struct net_device*) ; 

__attribute__((used)) static void tsi108_check_rxring(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);

	/* A poll is scheduled, as opposed to caling tsi108_refill_rx
	 * directly, so as to keep the receive path single-threaded
	 * (and thus not needing a lock).
	 */

	if (netif_running(dev) && data->rxfree < TSI108_RXRING_LEN / 4)
		tsi108_rx_int(dev);
}