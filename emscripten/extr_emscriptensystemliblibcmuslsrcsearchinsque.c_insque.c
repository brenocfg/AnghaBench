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
struct node {struct node* prev; struct node* next; } ;

/* Variables and functions */

void insque(void *element, void *pred)
{
	struct node *e = element;
	struct node *p = pred;

	if (!p) {
		e->next = e->prev = 0;
		return;
	}
	e->next = p->next;
	e->prev = p;
	p->next = e;
	if (e->next)
		e->next->prev = e;
}