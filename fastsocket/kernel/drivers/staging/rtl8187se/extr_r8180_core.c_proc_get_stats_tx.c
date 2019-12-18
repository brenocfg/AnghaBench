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
struct TYPE_2__ {unsigned long txnpokint; unsigned long txhpokint; unsigned long txlpokint; int /*<<< orphan*/  txbeaconerr; int /*<<< orphan*/  txbeacon; int /*<<< orphan*/  txretry; scalar_t__ txlperr; scalar_t__ txhperr; scalar_t__ txnperr; } ;
struct r8180_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 scalar_t__ snprintf (char*,int,char*,unsigned long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_get_stats_tx(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	int len = 0;
	unsigned long totalOK;

	totalOK=priv->stats.txnpokint+priv->stats.txhpokint+priv->stats.txlpokint;
	len += snprintf(page + len, count - len,
		"TX OK: %lu\n"
		"TX Error: %lu\n"
		"TX Retry: %lu\n"
		"TX beacon OK: %lu\n"
		"TX beacon error: %lu\n",
		totalOK,
		priv->stats.txnperr+priv->stats.txhperr+priv->stats.txlperr,
		priv->stats.txretry,
		priv->stats.txbeacon,
		priv->stats.txbeaconerr
	);

	*eof = 1;
	return len;
}