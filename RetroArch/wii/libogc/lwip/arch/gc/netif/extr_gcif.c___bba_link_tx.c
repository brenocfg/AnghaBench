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
typedef  int /*<<< orphan*/  u8 ;
struct pbuf {scalar_t__ tot_len; int /*<<< orphan*/  len; int /*<<< orphan*/  payload; struct pbuf* next; } ;
struct netif {scalar_t__ state; } ;
struct bba_priv {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int BBA_MINPKTSIZE ; 
 int /*<<< orphan*/  BBA_NCRA ; 
 int BBA_NCRA_ST0 ; 
 int BBA_NCRA_ST1 ; 
 int /*<<< orphan*/  BBA_TXFIFOCNT ; 
 scalar_t__ BBA_TX_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  BBA_WRTXFIFOD ; 
 int /*<<< orphan*/  ERR_ABRT ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_PKTSIZE ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWIP_ERROR (char*) ; 
 int /*<<< orphan*/  LWP_GetSelf () ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  __bba_exi_stop (struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_exi_wake (struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_tx_stop (struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_tx_wake (struct bba_priv*) ; 
 int /*<<< orphan*/  __linkstate (struct bba_priv*) ; 
 int /*<<< orphan*/  bba_deselect () ; 
 int bba_in8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_out12 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bba_out8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bba_outsdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bba_outsdata_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_outsregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_select () ; 

__attribute__((used)) static err_t __bba_link_tx(struct netif *dev,struct pbuf *p)
{
	u8 tmpbuf[BBA_MINPKTSIZE];
	struct pbuf *tmp;
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	__bba_tx_stop(priv);
	__bba_exi_stop(priv);

	if(p->tot_len>BBA_TX_MAX_PACKET_SIZE) {
		LWIP_ERROR(("__bba_link_tx(%d,%p) pkt_size\n",p->tot_len,LWP_GetSelf()));
		__bba_tx_wake(priv);
		__bba_exi_wake(priv);
		return ERR_PKTSIZE;
	}

	if(!__linkstate(priv)) {
		LWIP_ERROR(("__bba_link_tx(error link state)\n"));
		__bba_tx_wake(priv);
		__bba_exi_wake(priv);
		return ERR_ABRT;
	}

	LWIP_DEBUGF(NETIF_DEBUG,("__bba_link_tx(%d,%p)\n",p->tot_len,LWP_GetSelf()));

	bba_out12(BBA_TXFIFOCNT,p->tot_len);

	bba_select();
	bba_outsregister(BBA_WRTXFIFOD);
	for(tmp=p;tmp!=NULL;tmp=tmp->next) {
		bba_outsdata_fast(tmp->payload,tmp->len);
	}
	if(p->tot_len<BBA_MINPKTSIZE) bba_outsdata(tmpbuf,(BBA_MINPKTSIZE-p->tot_len));
	bba_deselect();

	bba_out8(BBA_NCRA,((bba_in8(BBA_NCRA)&~BBA_NCRA_ST0)|BBA_NCRA_ST1));		//&~BBA_NCRA_ST0
	__bba_exi_wake(priv);
	return ERR_OK;
}