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
struct TYPE_2__ {int /*<<< orphan*/  rxurberr; int /*<<< orphan*/  rxoverflow; int /*<<< orphan*/  rxrdu; int /*<<< orphan*/  rxint; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 scalar_t__ snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_get_stats_rx(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);

	int len = 0;

	len += snprintf(page + len, count - len,
		"RX packets: %lu\n"
		"RX desc err: %lu\n"
		"RX rx overflow error: %lu\n"
		"RX invalid urb error: %lu\n",
		priv->stats.rxint,
		priv->stats.rxrdu,
		priv->stats.rxoverflow,
		priv->stats.rxurberr);

	*eof = 1;
	return len;
}