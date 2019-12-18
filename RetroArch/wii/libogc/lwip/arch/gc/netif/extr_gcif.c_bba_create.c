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
struct netif {int mtu; int hwaddr_len; int /*<<< orphan*/ * hwaddr; int /*<<< orphan*/  flags; int /*<<< orphan*/  linkoutput; int /*<<< orphan*/  output; int /*<<< orphan*/ * name; } ;
struct eth_addr {int dummy; } ;
struct bba_priv {int /*<<< orphan*/  state; struct eth_addr* ethaddr; int /*<<< orphan*/  tq_xmit; } ;
typedef  struct bba_priv* dev_s ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  IFNAME0 ; 
 int /*<<< orphan*/  IFNAME1 ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWIP_ERROR (char*) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  NETIF_FLAG_BROADCAST ; 
 int /*<<< orphan*/  __bba_link_tx ; 
 int /*<<< orphan*/  __bba_start_tx ; 
 struct netif* gc_netif ; 
 scalar_t__ mem_malloc (int) ; 
 int /*<<< orphan*/  memset (struct bba_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_exi_queue ; 

dev_s bba_create(struct netif *dev)
{
	struct bba_priv *priv = NULL;

	LWIP_DEBUGF(NETIF_DEBUG, ("bba_create()\n"));

	priv = (struct bba_priv*)mem_malloc(sizeof(struct bba_priv));
	if(!priv) {
		LWIP_ERROR(("bba_create: out of memory for bba_priv\n"));
		return NULL;
	}
	memset(priv,0,sizeof(struct bba_priv));

	LWP_InitQueue(&priv->tq_xmit);
	LWP_InitQueue(&wait_exi_queue);

	dev->name[0] = IFNAME0;
	dev->name[1] = IFNAME1;
	dev->output = __bba_start_tx;
	dev->linkoutput = __bba_link_tx;
	dev->mtu = 1500;
	dev->flags = NETIF_FLAG_BROADCAST;
	dev->hwaddr_len = 6;

	priv->ethaddr = (struct eth_addr*)&(dev->hwaddr[0]);
	priv->state = ERR_OK;

	gc_netif = dev;
	return priv;
}