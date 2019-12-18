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
typedef  int u8 ;
struct r8192_priv {int /*<<< orphan*/  skb_queue; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb_aggQ; int /*<<< orphan*/ * skb_waitQ; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDR ; 
 int CR_RE ; 
 int CR_TE ; 
 int MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8192_rtx_disable(struct net_device *dev)
{
	u8 cmd;
	struct r8192_priv *priv = ieee80211_priv(dev);
        int i;

	cmd=read_nic_byte(dev,CMDR);
//	if(!priv->ieee80211->bSupportRemoteWakeUp) {
		write_nic_byte(dev, CMDR, cmd &~ \
				(CR_TE|CR_RE));
//	}
	force_pci_posting(dev);
	mdelay(30);

        for(i = 0; i < MAX_QUEUE_SIZE; i++) {
                skb_queue_purge(&priv->ieee80211->skb_waitQ [i]);
        }
        for(i = 0; i < MAX_QUEUE_SIZE; i++) {
                skb_queue_purge(&priv->ieee80211->skb_aggQ [i]);
        }


	skb_queue_purge(&priv->skb_queue);
	return;
}