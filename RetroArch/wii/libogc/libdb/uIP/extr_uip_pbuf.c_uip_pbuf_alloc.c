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
typedef  int uip_pbuf_layer ;
typedef  int uip_pbuf_flag ;
typedef  void u8_t ;
typedef  int u16_t ;
struct uip_pbuf {int tot_len; int len; int ref; void* flags; struct uip_pbuf* next; int /*<<< orphan*/ * payload; } ;
typedef  int s32_t ;

/* Variables and functions */
 void* MEM_ALIGN (void*) ; 
 scalar_t__ MEM_ALIGN_SIZE (int) ; 
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int /*<<< orphan*/  UIP_IP_HLEN ; 
 int /*<<< orphan*/  UIP_LL_HLEN ; 
 void* UIP_PBUF_FLAG_POOL ; 
 void* UIP_PBUF_FLAG_RAM ; 
 void* UIP_PBUF_FLAG_REF ; 
 void* UIP_PBUF_FLAG_ROM ; 
#define  UIP_PBUF_IP 135 
#define  UIP_PBUF_LINK 134 
#define  UIP_PBUF_POOL 133 
 int UIP_PBUF_POOL_BUFSIZE ; 
#define  UIP_PBUF_RAM 132 
#define  UIP_PBUF_RAW 131 
#define  UIP_PBUF_REF 130 
#define  UIP_PBUF_ROM 129 
#define  UIP_PBUF_TRANSPORT 128 
 int /*<<< orphan*/  UIP_TRANSPORT_HLEN ; 
 struct uip_pbuf* memb_alloc (int /*<<< orphan*/ *) ; 
 struct uip_pbuf* memr_malloc (scalar_t__) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pool_pbufs ; 
 int /*<<< orphan*/  uip_rom_pbufs ; 

struct uip_pbuf* uip_pbuf_alloc(uip_pbuf_layer layer,u16_t len,uip_pbuf_flag flag)
{
	u16_t offset;
	s32_t rem_len;
	struct uip_pbuf *p,*q,*r;

	offset = 0;
	switch(layer)	 {
		case UIP_PBUF_TRANSPORT:
			offset += UIP_TRANSPORT_HLEN;
		case UIP_PBUF_IP:
			offset += UIP_IP_HLEN;
		case UIP_PBUF_LINK:
			offset += UIP_LL_HLEN;
			break;
		case UIP_PBUF_RAW:
			break;
		default:
			UIP_ERROR("uip_pbuf_alloc: bad pbuf layer.\n");
			return NULL;
	}

	switch(flag) {
		case UIP_PBUF_POOL:
			p = memb_alloc(&uip_pool_pbufs);
			if(p==NULL) {
				UIP_ERROR("uip_pbuf_alloc: couldn't allocate pbuf(p) from pool\n");
				return NULL;
			}

			p->next = NULL;
			p->payload = MEM_ALIGN((void*)((u8_t*)p+(sizeof(struct uip_pbuf)+offset)));
			p->tot_len = len;
			p->len = (len>(UIP_PBUF_POOL_BUFSIZE-offset)?(UIP_PBUF_POOL_BUFSIZE-offset):len);
			p->flags = UIP_PBUF_FLAG_POOL;
			p->ref = 1;

			r = p;
			rem_len = len - p->len;
			while(rem_len>0) {
				q = memb_alloc(&uip_pool_pbufs);
				if(q==NULL) {
					UIP_ERROR("uip_pbuf_alloc: couldn't allocate pbuf(q) from pool\n");
					uip_pbuf_free(p);
					return NULL;
				}

				q->next = NULL;
				r->next = q;
				q->tot_len = rem_len;
				q->len = (rem_len>UIP_PBUF_POOL_BUFSIZE?UIP_PBUF_POOL_BUFSIZE:rem_len);
				q->payload = (void*)((u8_t*)q+sizeof(struct uip_pbuf));
				q->flags = UIP_PBUF_FLAG_POOL;
				q->ref = 1;

				rem_len -= q->len;
				r = q;
			}
			break;
		case UIP_PBUF_RAM:
			p = memr_malloc(MEM_ALIGN_SIZE(sizeof(struct uip_pbuf)+offset)+MEM_ALIGN_SIZE(len));
			if(p==NULL) {
				UIP_ERROR("uip_pbuf_alloc: couldn't allocate pbuf from ram\n");
				return NULL;
			}
			p->payload = MEM_ALIGN((u8_t*)p+sizeof(struct uip_pbuf)+offset);
			p->len = p->tot_len = len;
			p->next = NULL;
			p->flags = UIP_PBUF_FLAG_RAM;
			break;
		case UIP_PBUF_ROM:
		case UIP_PBUF_REF:
			p = memb_alloc(&uip_rom_pbufs);
			if(p==NULL) {
				UIP_ERROR("uip_pbuf_alloc: couldn't allocate pbuf from rom/ref\n");
				return NULL;
			}
			p->payload = NULL;
			p->next = NULL;
			p->len = p->tot_len = len;
			p->flags = (flag==UIP_PBUF_ROM?UIP_PBUF_FLAG_ROM:UIP_PBUF_FLAG_REF);
			break;
		default:
			UIP_ERROR("uip_pbuf_alloc: bad flag value.\n");
			return NULL;
	}

	p->ref = 1;
	return p;
}