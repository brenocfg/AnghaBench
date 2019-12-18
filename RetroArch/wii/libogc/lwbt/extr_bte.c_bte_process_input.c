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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pbuf {int* payload; int /*<<< orphan*/  tot_len; } ;
struct l2cap_pcb {int dummy; } ;
struct bte_pcb {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_OK ; 
 int HIDP_HDR_PARAM_MASK ; 
 int HIDP_HDR_TRANS_MASK ; 
#define  HIDP_TRANS_DATA 130 
#define  HIDP_TRANS_HANDSHAKE 129 
#define  HIDP_TRANS_HIDCONTROL 128 
 int /*<<< orphan*/  LOG (char*,struct bte_pcb*,struct pbuf*) ; 
 scalar_t__ STATE_DISCONNECTED ; 
 scalar_t__ STATE_DISCONNECTING ; 
 int /*<<< orphan*/  bte_process_data (struct bte_pcb*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bte_process_handshake (struct bte_pcb*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t bte_process_input(void *arg,struct l2cap_pcb *pcb,struct pbuf *p,err_t err)
{
	u8 *buf;
	u16 len;
	u8 hdr,type,param;
	struct bte_pcb *bte = (struct bte_pcb*)arg;

	LOG("bte_process_input(%p,%p)\n",bte,p);

	if(bte->state==STATE_DISCONNECTING
		|| bte->state==STATE_DISCONNECTED) return ERR_CLSD;

	buf = p->payload;
	len = p->tot_len;

	len--;
	hdr = *buf++;
	type = (hdr&HIDP_HDR_TRANS_MASK);
	param = (hdr&HIDP_HDR_PARAM_MASK);
	switch(type) {
		case HIDP_TRANS_HANDSHAKE:
			bte_process_handshake(bte,param,buf,len);
			break;
		case HIDP_TRANS_HIDCONTROL:
			break;
		case HIDP_TRANS_DATA:
			bte_process_data(bte,param,buf,len);
			break;
		default:
			break;
	}
	return ERR_OK;
}