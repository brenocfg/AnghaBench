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
struct pbuf {scalar_t__ len; scalar_t__ tot_len; struct pbuf* next; } ;

/* Variables and functions */
 scalar_t__ btpbuf_free (struct pbuf*) ; 

struct pbuf* btpbuf_dechain(struct pbuf *p)
{
	struct pbuf *q;
	u8_t tail_gone = 1;

	q = p->next;
	if(q!=NULL) {
		q->tot_len = p->tot_len - p->len;
		p->next = NULL;
		p->tot_len = p->len;

		tail_gone = btpbuf_free(q);
	}

	return (tail_gone>0?NULL:q);
}