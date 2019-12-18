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
struct net_device_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct gfar_extra_stats {int /*<<< orphan*/  rx_overrun; int /*<<< orphan*/  rx_crcerr; int /*<<< orphan*/  rx_nonoctet; int /*<<< orphan*/  rx_short; int /*<<< orphan*/  rx_large; int /*<<< orphan*/  rx_trunc; } ;
struct gfar_private {struct gfar_extra_stats extra_stats; } ;

/* Variables and functions */
 unsigned short RXBD_CRCERR ; 
 unsigned short RXBD_LARGE ; 
 unsigned short RXBD_NONOCTET ; 
 unsigned short RXBD_OVERRUN ; 
 unsigned short RXBD_SHORT ; 
 unsigned short RXBD_TRUNCATED ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void count_errors(unsigned short status, struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct gfar_extra_stats *estats = &priv->extra_stats;

	/* If the packet was truncated, none of the other errors
	 * matter */
	if (status & RXBD_TRUNCATED) {
		stats->rx_length_errors++;

		estats->rx_trunc++;

		return;
	}
	/* Count the errors, if there were any */
	if (status & (RXBD_LARGE | RXBD_SHORT)) {
		stats->rx_length_errors++;

		if (status & RXBD_LARGE)
			estats->rx_large++;
		else
			estats->rx_short++;
	}
	if (status & RXBD_NONOCTET) {
		stats->rx_frame_errors++;
		estats->rx_nonoctet++;
	}
	if (status & RXBD_CRCERR) {
		estats->rx_crcerr++;
		stats->rx_crc_errors++;
	}
	if (status & RXBD_OVERRUN) {
		estats->rx_overrun++;
		stats->rx_crc_errors++;
	}
}