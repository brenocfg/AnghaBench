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
struct pbuf {scalar_t__ tot_len; scalar_t__ len; struct pbuf* next; } ;

/* Variables and functions */

struct pbuf* btpbuf_dequeue(struct pbuf *p)
{
	struct pbuf *q;

	if(p==NULL) return NULL;

	while(p->tot_len!=p->len) p = p->next;

	q = p->next;
	p->next = NULL;

	return q;
}