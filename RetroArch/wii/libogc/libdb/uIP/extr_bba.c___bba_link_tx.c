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
typedef  scalar_t__ u32 ;
struct uip_pbuf {scalar_t__ tot_len; scalar_t__ len; int /*<<< orphan*/ * payload; struct uip_pbuf* next; } ;
struct uip_netif {int dummy; } ;
typedef  int /*<<< orphan*/  s8_t ;

/* Variables and functions */
 scalar_t__ BBA_MINPKTSIZE ; 
 int /*<<< orphan*/  BBA_NCRA ; 
 int BBA_NCRA_ST0 ; 
 int BBA_NCRA_ST1 ; 
 int /*<<< orphan*/  BBA_TXFIFOCNT ; 
 scalar_t__ BBA_TX_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  BBA_WRTXFIFOD ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIP_ERR_ABRT ; 
 int /*<<< orphan*/  UIP_ERR_IF ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_ERR_PKTSIZE ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  __linkstate () ; 
 int /*<<< orphan*/  bba_deselect () ; 
 int bba_in8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_out12 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bba_out8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bba_outsdata (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bba_outsregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_select () ; 

__attribute__((used)) static s8_t __bba_link_tx(struct uip_netif *dev,struct uip_pbuf *p)
{
	u8 pad[60];
	u32 len;
	struct uip_pbuf *tmp;

	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,NULL)==0) return UIP_ERR_IF;

	if(p->tot_len>BBA_TX_MAX_PACKET_SIZE) {
		UIP_LOG("__bba_link_tx: packet dropped due to big buffer.\n");
		EXI_Unlock(EXI_CHANNEL_0);
		return UIP_ERR_PKTSIZE;
	}

	if(!__linkstate()) {
		EXI_Unlock(EXI_CHANNEL_0);
		return UIP_ERR_ABRT;
	}

	while((bba_in8(BBA_NCRA)&(BBA_NCRA_ST0|BBA_NCRA_ST1)));

	len = p->tot_len;
	bba_out12(BBA_TXFIFOCNT,len);

	bba_select();
	bba_outsregister(BBA_WRTXFIFOD);
	for(tmp=p;tmp!=NULL;tmp=tmp->next) {
		bba_outsdata(tmp->payload,tmp->len);
	}
	if(len<BBA_MINPKTSIZE) {
		len = (BBA_MINPKTSIZE-len);
		bba_outsdata(pad,len);
	}
	bba_deselect();

	bba_out8(BBA_NCRA,((bba_in8(BBA_NCRA)&~BBA_NCRA_ST0)|BBA_NCRA_ST1));		//&~BBA_NCRA_ST0
	EXI_Unlock(EXI_CHANNEL_0);
	return UIP_ERR_OK;
}