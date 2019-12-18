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
typedef  int u16_t ;
struct uip_tcp_pcb {int dummy; } ;
struct uip_pbuf {int tot_len; } ;
struct tcpip_sock {struct uip_pbuf* lastdata; } ;
typedef  int /*<<< orphan*/  s8_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_ERR_VAL ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_queue (struct uip_pbuf*,struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_tcp_recved (struct uip_tcp_pcb*,int) ; 

__attribute__((used)) static s8_t tcpip_recved(void *arg,struct uip_tcp_pcb *pcb,struct uip_pbuf *p,s8_t err)
{
	u16_t len;
	struct tcpip_sock *sock = (struct tcpip_sock*)arg;

	//printf("tcpip_recved(%s (%d/%d))\n",(u8_t*)p->payload,p->len,p->tot_len);
	if(!sock) {
		uip_pbuf_free(p);
		return UIP_ERR_VAL;
	}

	if(p) {
		len = p->tot_len;
		if(sock->lastdata==NULL) {
			sock->lastdata = p;
		} else {
/*
			qcnt++;
			printf("tcpip_recved(queuing %d)\n",qcnt);
*/
			uip_pbuf_queue(sock->lastdata,p);
		}
	} else
		len = 1;

	uip_tcp_recved(pcb,len);
	return UIP_ERR_OK;
}