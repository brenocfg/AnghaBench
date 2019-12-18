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
typedef  scalar_t__ u8_t ;
struct uip_pbuf {scalar_t__ len; scalar_t__ tot_len; struct uip_pbuf* next; } ;

/* Variables and functions */
 scalar_t__ uip_pbuf_free (struct uip_pbuf*) ; 

struct uip_pbuf* uip_pbuf_dechain(struct uip_pbuf *p)
{
	struct uip_pbuf *q;
	u8_t tail_gone = 1;

	q = p->next;
	if(q!=NULL) {
		q->tot_len = p->tot_len - p->len;
		p->next = NULL;
		p->tot_len = p->len;

		tail_gone = uip_pbuf_free(q);
	}

	return (tail_gone>0?NULL:q);
}