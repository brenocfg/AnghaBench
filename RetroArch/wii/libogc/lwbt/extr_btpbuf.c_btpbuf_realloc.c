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
typedef  scalar_t__ u16_t ;
struct pbuf {scalar_t__ tot_len; scalar_t__ len; scalar_t__ flags; struct pbuf* next; scalar_t__ payload; } ;
typedef  scalar_t__ s16_t ;

/* Variables and functions */
 scalar_t__ PBUF_FLAG_RAM ; 
 int /*<<< orphan*/  btmemr_realloc (struct pbuf*,scalar_t__) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 

void btpbuf_realloc(struct pbuf *p,u16_t new_len)
{
	u16_t rem_len;
	s16_t grow;
	struct pbuf *q;

	if(new_len>=p->tot_len) return;

	grow = new_len - p->tot_len;
	rem_len = new_len;
	q = p;
	while(rem_len>q->len) {
		rem_len -= q->len;
		q->tot_len += grow;
		q = q->next;
	}

	if(q->flags==PBUF_FLAG_RAM && rem_len!=q->len)
		btmemr_realloc(q,(u8_t*)q->payload-(u8_t*)q+rem_len);

	q->len = rem_len;
	q->tot_len = q->len;

	if(q->next!=NULL) btpbuf_free(q->next);
	q->next = NULL;
}