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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct uip_pbuf {scalar_t__ payload; struct uip_pbuf* next; } ;
struct uip_netif {int dummy; } ;
struct bba_descr {int dummy; } ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ packet_len; scalar_t__ status; int next_packet_ptr; } ;

/* Variables and functions */
 int BBA_INIT_RHBP ; 
 int BBA_INIT_RRP ; 
 int /*<<< orphan*/  BBA_RRP ; 
 int /*<<< orphan*/  BBA_RWP ; 
 scalar_t__ BBA_RX_MAX_PACKET_SIZE ; 
 scalar_t__ BBA_RX_STATUS_FAE ; 
 scalar_t__ BBA_RX_STATUS_RERR ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 int /*<<< orphan*/  EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  UIP_PBUF_POOL ; 
 int /*<<< orphan*/  UIP_PBUF_RAW ; 
 int /*<<< orphan*/  bba_deselect () ; 
 int bba_in12 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_ins (int,void*,int) ; 
 int /*<<< orphan*/  bba_insdata (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bba_insregister (int) ; 
 int /*<<< orphan*/  bba_out12 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bba_process (struct uip_pbuf*,struct uip_netif*) ; 
 int /*<<< orphan*/  bba_select () ; 
 TYPE_1__ cur_descr ; 
 int /*<<< orphan*/  le32_to_cpus (scalar_t__*) ; 
 struct uip_pbuf* uip_pbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s8_t bba_start_rx(struct uip_netif *dev,u32 budget)
{
	s32 size;
	u16 top,pos,rwp,rrp;
	u32 pkt_status,recvd;
	struct uip_pbuf *p,*q;

	UIP_LOG("bba_start_rx()\n");

	recvd = 0;
	rwp = bba_in12(BBA_RWP);
	rrp = bba_in12(BBA_RRP);
	while(recvd<budget && rrp!=rwp) {
		bba_ins(rrp<<8,(void*)(&cur_descr),sizeof(struct bba_descr));
		le32_to_cpus((u32*)((void*)(&cur_descr)));

		size = cur_descr.packet_len - 4;
		pkt_status = cur_descr.status;
		if(size>(BBA_RX_MAX_PACKET_SIZE+4)) {
			UIP_LOG("bba_start_rx: packet dropped due to big buffer.\n");
			continue;
		}

		if(pkt_status&(BBA_RX_STATUS_RERR|BBA_RX_STATUS_FAE)) {
			UIP_LOG("bba_start_rx: packet dropped due to receive errors.\n");
			rwp = bba_in12(BBA_RWP);
			rrp = bba_in12(BBA_RRP);
			continue;
		}

		pos = (rrp<<8)+4;
		top = (BBA_INIT_RHBP+1)<<8;

		p = uip_pbuf_alloc(UIP_PBUF_RAW,size,UIP_PBUF_POOL);
		if(p) {
			for(q=p;q!=NULL;q=q->next) {
				bba_select();
				bba_insregister(pos);
				if((pos+size)<top) {
					bba_insdata(q->payload,size);
				} else {
					s32 chunk = top-pos;

					size -= chunk;
					pos = BBA_INIT_RRP<<8;
					bba_insdata(q->payload,chunk);
					bba_deselect();

					bba_select();
					bba_insregister(pos);
					bba_insdata(q->payload+chunk,size);
				}
				bba_deselect();
				pos += size;
			}

			EXI_Unlock(EXI_CHANNEL_0);
			bba_process(p,dev);
			EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,NULL);
		} else
			break;

		recvd++;

		bba_out12(BBA_RRP,(rrp=cur_descr.next_packet_ptr));
		rwp = bba_in12(BBA_RWP);
	}
	return UIP_ERR_OK;
}