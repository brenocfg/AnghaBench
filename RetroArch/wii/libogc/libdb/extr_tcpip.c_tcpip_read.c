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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
struct uip_pbuf {scalar_t__ len; scalar_t__ payload; } ;
struct tcpip_sock {scalar_t__ lastoffset; struct uip_pbuf* lastdata; } ;
typedef  int s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  __tcpip_poll () ; 
 struct tcpip_sock* tcpip_getsocket (int) ; 
 struct uip_pbuf* uip_pbuf_dequeue (struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 

s32_t tcpip_read(s32_t s,void *buffer,u32_t len)
{
	u32_t off,copy;
	u8_t *ptr;
	struct uip_pbuf *p;
	struct tcpip_sock *sock;

	sock = tcpip_getsocket(s);
	if(!sock) return -1;

	do {
		__tcpip_poll();
	} while(sock->lastdata==NULL);

	if(sock->lastdata) {
		off = 0;
		ptr = buffer;
		while(len>0 && sock->lastdata) {
			p = sock->lastdata;

			if(len>p->len-sock->lastoffset) copy = (p->len-sock->lastoffset);
			else copy = len;

			UIP_MEMCPY(ptr+off,(u8_t*)p->payload+sock->lastoffset,copy);

			off += copy;
			len -= copy;
			sock->lastoffset += copy;

			if(sock->lastoffset>=p->len) {
				sock->lastoffset = 0;
				sock->lastdata = uip_pbuf_dequeue(p);
				uip_pbuf_free(p);
/*
				if(qcnt>0) {
					printf("tcpip_read(dequeuing %d)\n",--qcnt);
				}
*/
			}
		}
		return off;
	}
	return -1;
}