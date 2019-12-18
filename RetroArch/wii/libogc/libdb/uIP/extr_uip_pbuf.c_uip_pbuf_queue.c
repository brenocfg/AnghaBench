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
struct uip_pbuf {struct uip_pbuf* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  uip_pbuf_ref (struct uip_pbuf*) ; 

void uip_pbuf_queue(struct uip_pbuf *p,struct uip_pbuf *n)
{
	if(p==NULL || n==NULL || p==n) return;

	while(p->next!=NULL) p = p->next;

	p->next = n;
	uip_pbuf_ref(n);
}