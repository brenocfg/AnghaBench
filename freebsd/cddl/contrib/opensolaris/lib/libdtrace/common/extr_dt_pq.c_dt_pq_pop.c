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
typedef  int uint_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int dtpq_last; int /*<<< orphan*/ ** dtpq_items; } ;
typedef  TYPE_1__ dt_pq_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_pq_getvalue (TYPE_1__*,int) ; 

void *
dt_pq_pop(dt_pq_t *p)
{
	uint_t i = 1;
	void *ret;

	assert(p->dtpq_last > 0);

	if (p->dtpq_last == 1)
		return (NULL);

	ret = p->dtpq_items[1];

	p->dtpq_last--;
	p->dtpq_items[1] = p->dtpq_items[p->dtpq_last];
	p->dtpq_items[p->dtpq_last] = NULL;

	for (;;) {
		uint_t lc = i * 2;
		uint_t rc = i * 2 + 1;
		uint_t c;
		uint64_t v;
		void *tmp;

		if (lc >= p->dtpq_last)
			break;

		if (rc >= p->dtpq_last) {
			c = lc;
			v = dt_pq_getvalue(p, lc);
		} else {
			uint64_t lv = dt_pq_getvalue(p, lc);
			uint64_t rv = dt_pq_getvalue(p, rc);

			if (lv < rv) {
				c = lc;
				v = lv;
			} else {
				c = rc;
				v = rv;
			}
		}

		if (v >= dt_pq_getvalue(p, i))
			break;

		tmp = p->dtpq_items[i];
		p->dtpq_items[i] = p->dtpq_items[c];
		p->dtpq_items[c] = tmp;

		i = c;
	}

	return (ret);
}