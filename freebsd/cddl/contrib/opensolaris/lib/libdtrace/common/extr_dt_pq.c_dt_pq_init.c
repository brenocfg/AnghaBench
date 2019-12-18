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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pq_value_f ;
struct TYPE_4__ {int dtpq_size; int dtpq_last; void* dtpq_arg; int /*<<< orphan*/  dtpq_value; int /*<<< orphan*/ * dtpq_hdl; int /*<<< orphan*/ * dtpq_items; } ;
typedef  TYPE_1__ dt_pq_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* dt_zalloc (int /*<<< orphan*/ *,int) ; 

dt_pq_t *
dt_pq_init(dtrace_hdl_t *dtp, uint_t size, dt_pq_value_f value_cb, void *cb_arg)
{
	dt_pq_t *p;
	assert(size > 1);

	if ((p = dt_zalloc(dtp, sizeof (dt_pq_t))) == NULL)
		return (NULL);

	p->dtpq_items = dt_zalloc(dtp, size * sizeof (p->dtpq_items[0]));
	if (p->dtpq_items == NULL) {
		dt_free(dtp, p);
		return (NULL);
	}

	p->dtpq_hdl = dtp;
	p->dtpq_size = size;
	p->dtpq_last = 1;
	p->dtpq_value = value_cb;
	p->dtpq_arg = cb_arg;

	return (p);
}