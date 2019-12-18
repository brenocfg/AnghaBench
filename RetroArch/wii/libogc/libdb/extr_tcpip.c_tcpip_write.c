#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32_t ;
typedef  scalar_t__ u16_t ;
struct tcpip_sock {TYPE_1__* pcb; } ;
typedef  scalar_t__ s8_t ;
typedef  int s32_t ;
struct TYPE_4__ {int flags; int snd_queuelen; int /*<<< orphan*/  unacked; } ;

/* Variables and functions */
 scalar_t__ UIP_ERR_OK ; 
 int UIP_TF_NODELAY ; 
 int /*<<< orphan*/  __tcpip_poll () ; 
 struct tcpip_sock* tcpip_getsocket (int) ; 
 scalar_t__ uip_tcp_sndbuf (TYPE_1__*) ; 
 scalar_t__ uip_tcp_write (TYPE_1__*,void const*,scalar_t__,int) ; 
 int /*<<< orphan*/  uip_tcpoutput (TYPE_1__*) ; 

s32_t tcpip_write(s32_t s,const void *buffer,u32_t len)
{
	s8_t err;
	u16_t snd_buf,copy;
	struct tcpip_sock *sock;

	sock = tcpip_getsocket(s);
	if(!sock) return -1;

//	printf("tcpip_write()\n");
	while(len>0) {
		do {
			__tcpip_poll();
		} while((snd_buf=uip_tcp_sndbuf(sock->pcb))==0);

		if(len>snd_buf) copy = snd_buf;
		else copy = len;

		err = uip_tcp_write(sock->pcb,buffer,copy,1);
		if(err==UIP_ERR_OK && (!sock->pcb->unacked || sock->pcb->flags&UIP_TF_NODELAY || sock->pcb->snd_queuelen>1))
			uip_tcpoutput(sock->pcb);

		buffer = buffer+copy;
		len -= copy;
	}
	return UIP_ERR_OK;
}