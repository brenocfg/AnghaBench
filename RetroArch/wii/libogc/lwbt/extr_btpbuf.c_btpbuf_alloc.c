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
typedef  void u8_t ;
typedef  int u16_t ;
struct pbuf {int tot_len; int len; int ref; void* flags; struct pbuf* next; int /*<<< orphan*/ * payload; } ;
typedef  int s32_t ;
typedef  int pbuf_layer ;
typedef  int pbuf_flag ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  LL_HLEN ; 
 void* MEM_ALIGN (void*) ; 
 scalar_t__ MEM_ALIGN_SIZE (int) ; 
 void* PBUF_FLAG_POOL ; 
 void* PBUF_FLAG_RAM ; 
 void* PBUF_FLAG_REF ; 
 void* PBUF_FLAG_ROM ; 
#define  PBUF_LINK 134 
#define  PBUF_POOL 133 
 int PBUF_POOL_BUFSIZE ; 
#define  PBUF_RAM 132 
#define  PBUF_RAW 131 
#define  PBUF_REF 130 
#define  PBUF_ROM 129 
#define  PBUF_TRANSPORT 128 
 int /*<<< orphan*/  TRANSPORT_HLEN ; 
 struct pbuf* btmemb_alloc (int /*<<< orphan*/ *) ; 
 struct pbuf* btmemr_malloc (scalar_t__) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pool_pbufs ; 
 int /*<<< orphan*/  rom_pbufs ; 

struct pbuf* btpbuf_alloc(pbuf_layer layer,u16_t len,pbuf_flag flag)
{
	u16_t offset;
	s32_t rem_len;
	struct pbuf *p,*q,*r;

	offset = 0;
	switch(layer)	 {
		case PBUF_TRANSPORT:
			offset += TRANSPORT_HLEN;
		case PBUF_LINK:
			offset += LL_HLEN;
			break;
		case PBUF_RAW:
			break;
		default:
			ERROR("btpbuf_alloc: bad pbuf layer.\n");
			return NULL;
	}

	switch(flag) {
		case PBUF_POOL:
			p = btmemb_alloc(&pool_pbufs);
			if(p==NULL) {
				ERROR("btbtpbuf_alloc: couldn't allocate pbuf(p) from pool\n");
				return NULL;
			}

			p->next = NULL;
			p->payload = MEM_ALIGN((void*)((u8_t*)p+(sizeof(struct pbuf)+offset)));
			p->tot_len = len;
			p->len = (len>(PBUF_POOL_BUFSIZE-offset)?(PBUF_POOL_BUFSIZE-offset):len);
			p->flags = PBUF_FLAG_POOL;
			p->ref = 1;

			r = p;
			rem_len = len - p->len;
			while(rem_len>0) {
				q = btmemb_alloc(&pool_pbufs);
				if(q==NULL) {
					ERROR("btpbuf_alloc: couldn't allocate pbuf(q) from pool\n");
					btpbuf_free(p);
					return NULL;
				}

				q->next = NULL;
				r->next = q;
				q->tot_len = rem_len;
				q->len = (rem_len>PBUF_POOL_BUFSIZE?PBUF_POOL_BUFSIZE:rem_len);
				q->payload = (void*)((u8_t*)q+sizeof(struct pbuf));
				q->flags = PBUF_FLAG_POOL;
				q->ref = 1;

				rem_len -= q->len;
				r = q;
			}
			break;
		case PBUF_RAM:
			p = btmemr_malloc(MEM_ALIGN_SIZE(sizeof(struct pbuf)+offset)+MEM_ALIGN_SIZE(len));
			if(p==NULL) {
				ERROR("btpbuf_alloc: couldn't allocate pbuf from ram\n");
				return NULL;
			}
			p->payload = MEM_ALIGN((u8_t*)p+sizeof(struct pbuf)+offset);
			p->len = p->tot_len = len;
			p->next = NULL;
			p->flags = PBUF_FLAG_RAM;
			break;
		case PBUF_ROM:
		case PBUF_REF:
			p = btmemb_alloc(&rom_pbufs);
			if(p==NULL) {
				ERROR("btpbuf_alloc: couldn't allocate pbuf from rom/ref\n");
				return NULL;
			}
			p->payload = NULL;
			p->next = NULL;
			p->len = p->tot_len = len;
			p->flags = (flag==PBUF_ROM?PBUF_FLAG_ROM:PBUF_FLAG_REF);
			break;
		default:
			ERROR("btpbuf_alloc: bad flag value.\n");
			return NULL;
	}

	p->ref = 1;
	return p;
}