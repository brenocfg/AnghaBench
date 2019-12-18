#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_4__ {scalar_t__ dtpq_last; scalar_t__ dtpq_size; void** dtpq_items; } ;
typedef  TYPE_1__ dt_pq_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_pq_getvalue (TYPE_1__*,size_t) ; 

void
dt_pq_insert(dt_pq_t *p, void *item)
{
	uint_t i;

	assert(p->dtpq_last < p->dtpq_size);

	i = p->dtpq_last++;
	p->dtpq_items[i] = item;

	while (i > 1 && dt_pq_getvalue(p, i) < dt_pq_getvalue(p, i / 2)) {
		void *tmp = p->dtpq_items[i];
		p->dtpq_items[i] = p->dtpq_items[i / 2];
		p->dtpq_items[i / 2] = tmp;
		i /= 2;
	}
}