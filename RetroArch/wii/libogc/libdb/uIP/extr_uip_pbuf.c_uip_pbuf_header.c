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
typedef  int u8_t ;
struct uip_pbuf {int* payload; scalar_t__ flags; scalar_t__ len; int /*<<< orphan*/  tot_len; } ;
typedef  scalar_t__ s16_t ;

/* Variables and functions */
 scalar_t__ UIP_PBUF_FLAG_POOL ; 
 scalar_t__ UIP_PBUF_FLAG_RAM ; 
 scalar_t__ UIP_PBUF_FLAG_REF ; 
 scalar_t__ UIP_PBUF_FLAG_ROM ; 

u8_t uip_pbuf_header(struct uip_pbuf *p,s16_t hdr_size_inc)
{
	void *payload;

	if(hdr_size_inc==0 || p==NULL) return 0;

	payload = p->payload;
	if(p->flags==UIP_PBUF_FLAG_POOL || p->flags==UIP_PBUF_FLAG_RAM) {
		p->payload = (u8_t*)p->payload-hdr_size_inc;
		if((u8_t*)p->payload<(u8_t*)p+sizeof(struct uip_pbuf)) {
			p->payload = payload;
			return 1;
		}
	} else if(p->flags==UIP_PBUF_FLAG_ROM || p->flags==UIP_PBUF_FLAG_REF) {
		if(hdr_size_inc<0 && hdr_size_inc-p->len<=0) p->payload = (u8_t*)p->payload-hdr_size_inc;
		else return 1;
	}
	p->tot_len += hdr_size_inc;
	p->len += hdr_size_inc;

	return 0;
}