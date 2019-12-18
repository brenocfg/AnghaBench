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
typedef  int /*<<< orphan*/  u32 ;
struct r8180_priv {int txringcount; int /*<<< orphan*/ * txhpringtail; int /*<<< orphan*/ * txhpringhead; int /*<<< orphan*/ * txvopringtail; int /*<<< orphan*/ * txvopringhead; int /*<<< orphan*/ * txvipringtail; int /*<<< orphan*/ * txvipringhead; int /*<<< orphan*/ * txbepringtail; int /*<<< orphan*/ * txbepringhead; int /*<<< orphan*/ * txbkpringtail; int /*<<< orphan*/ * txbkpringhead; int /*<<< orphan*/ * txmapringtail; int /*<<< orphan*/ * txmapringhead; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  BE_PRIORITY 133 
#define  BK_PRIORITY 132 
 int /*<<< orphan*/  DMESG (char*) ; 
#define  HI_PRIORITY 131 
#define  MANAGE_PRIORITY 130 
#define  VI_PRIORITY 129 
#define  VO_PRIORITY 128 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

int get_curr_tx_free_desc(struct net_device *dev, int priority)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u32* tail;
	u32* head;
	int ret;

	switch (priority){
		case MANAGE_PRIORITY:
			head = priv->txmapringhead;
			tail = priv->txmapringtail;
			break;
		case BK_PRIORITY:
			head = priv->txbkpringhead;
			tail = priv->txbkpringtail;
			break;
		case BE_PRIORITY:
			head = priv->txbepringhead;
			tail = priv->txbepringtail;
			break;
		case VI_PRIORITY:
			head = priv->txvipringhead;
			tail = priv->txvipringtail;
			break;
		case VO_PRIORITY:
			head = priv->txvopringhead;
			tail = priv->txvopringtail;
			break;
		case HI_PRIORITY:
			head = priv->txhpringhead;
			tail = priv->txhpringtail;
			break;
		default:
			return -1;
	}

	if (head <= tail)
		ret = priv->txringcount - (tail - head)/8;
	else
		ret = (head - tail)/8;

	if (ret > priv->txringcount)
		DMESG("BUG");

	return ret;
}