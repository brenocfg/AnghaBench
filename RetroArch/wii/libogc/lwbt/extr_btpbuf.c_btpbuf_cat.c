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
struct pbuf {struct pbuf* next; scalar_t__ tot_len; } ;

/* Variables and functions */

void btpbuf_cat(struct pbuf *h,struct pbuf *t)
{
	struct pbuf *p;

	if(h==NULL || t==NULL) return;

	for(p=h;p->next!=NULL;p=p->next) {
		p->tot_len += t->tot_len;
	}
	p->tot_len += t->tot_len;
	p->next = t;
}