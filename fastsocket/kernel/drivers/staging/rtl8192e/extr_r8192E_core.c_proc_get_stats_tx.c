#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int txviokint; int /*<<< orphan*/  txoverflow; int /*<<< orphan*/  txcmdpktokint; int /*<<< orphan*/  txbeaconerr; int /*<<< orphan*/  txbeaconokint; int /*<<< orphan*/  txmanageokint; int /*<<< orphan*/  txbkokint; int /*<<< orphan*/  txbeokint; int /*<<< orphan*/  txvookint; } ;
struct r8192_priv {TYPE_3__ stats; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 scalar_t__ snprintf (char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_get_stats_tx(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);

	int len = 0;

	len += snprintf(page + len, count - len,
		"TX VI priority ok int: %lu\n"
//		"TX VI priority error int: %lu\n"
		"TX VO priority ok int: %lu\n"
//		"TX VO priority error int: %lu\n"
		"TX BE priority ok int: %lu\n"
//		"TX BE priority error int: %lu\n"
		"TX BK priority ok int: %lu\n"
//		"TX BK priority error int: %lu\n"
		"TX MANAGE priority ok int: %lu\n"
//		"TX MANAGE priority error int: %lu\n"
		"TX BEACON priority ok int: %lu\n"
		"TX BEACON priority error int: %lu\n"
		"TX CMDPKT priority ok int: %lu\n"
//		"TX high priority ok int: %lu\n"
//		"TX high priority failed error int: %lu\n"
//		"TX queue resume: %lu\n"
		"TX queue stopped?: %d\n"
		"TX fifo overflow: %lu\n"
//		"TX beacon: %lu\n"
//		"TX VI queue: %d\n"
//		"TX VO queue: %d\n"
//		"TX BE queue: %d\n"
//		"TX BK queue: %d\n"
//		"TX HW queue: %d\n"
//		"TX VI dropped: %lu\n"
//		"TX VO dropped: %lu\n"
//		"TX BE dropped: %lu\n"
//		"TX BK dropped: %lu\n"
		"TX total data packets %lu\n"
		"TX total data bytes :%lu\n",
//		"TX beacon aborted: %lu\n",
		priv->stats.txviokint,
//		priv->stats.txvierr,
		priv->stats.txvookint,
//		priv->stats.txvoerr,
		priv->stats.txbeokint,
//		priv->stats.txbeerr,
		priv->stats.txbkokint,
//		priv->stats.txbkerr,
		priv->stats.txmanageokint,
//		priv->stats.txmanageerr,
		priv->stats.txbeaconokint,
		priv->stats.txbeaconerr,
		priv->stats.txcmdpktokint,
//		priv->stats.txhpokint,
//		priv->stats.txhperr,
//		priv->stats.txresumed,
		netif_queue_stopped(dev),
		priv->stats.txoverflow,
//		priv->stats.txbeacon,
//		atomic_read(&(priv->tx_pending[VI_QUEUE])),
//		atomic_read(&(priv->tx_pending[VO_QUEUE])),
//		atomic_read(&(priv->tx_pending[BE_QUEUE])),
//		atomic_read(&(priv->tx_pending[BK_QUEUE])),
//		read_nic_byte(dev, TXFIFOCOUNT),
//		priv->stats.txvidrop,
//		priv->stats.txvodrop,
		priv->ieee80211->stats.tx_packets,
		priv->ieee80211->stats.tx_bytes


//		priv->stats.txbedrop,
//		priv->stats.txbkdrop
			//	priv->stats.txdatapkt
//		priv->stats.txbeaconerr
		);

	*eof = 1;
	return len;
}