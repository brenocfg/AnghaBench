#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_7__ {struct net_device_stats net_stats; } ;
struct vxgedev {int no_of_vpath; TYPE_6__* vpaths; TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_frms; } ;
struct TYPE_11__ {TYPE_4__ stats; } ;
struct TYPE_8__ {scalar_t__ rx_dropped; scalar_t__ rx_mcast; scalar_t__ rx_errors; scalar_t__ rx_bytes; scalar_t__ rx_frms; } ;
struct TYPE_9__ {TYPE_2__ stats; } ;
struct TYPE_12__ {TYPE_5__ fifo; TYPE_3__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 struct vxgedev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *
vxge_get_stats(struct net_device *dev)
{
	struct vxgedev *vdev;
	struct net_device_stats *net_stats;
	int k;

	vdev = netdev_priv(dev);

	net_stats = &vdev->stats.net_stats;

	memset(net_stats, 0, sizeof(struct net_device_stats));

	for (k = 0; k < vdev->no_of_vpath; k++) {
		net_stats->rx_packets += vdev->vpaths[k].ring.stats.rx_frms;
		net_stats->rx_bytes += vdev->vpaths[k].ring.stats.rx_bytes;
		net_stats->rx_errors += vdev->vpaths[k].ring.stats.rx_errors;
		net_stats->multicast += vdev->vpaths[k].ring.stats.rx_mcast;
		net_stats->rx_dropped +=
			vdev->vpaths[k].ring.stats.rx_dropped;

		net_stats->tx_packets += vdev->vpaths[k].fifo.stats.tx_frms;
		net_stats->tx_bytes += vdev->vpaths[k].fifo.stats.tx_bytes;
		net_stats->tx_errors += vdev->vpaths[k].fifo.stats.tx_errors;
	}

	return net_stats;
}