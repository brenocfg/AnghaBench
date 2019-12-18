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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {struct TYPE_4__* dtpq_items; int /*<<< orphan*/ * dtpq_hdl; } ;
typedef  TYPE_1__ dt_pq_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
dt_pq_fini(dt_pq_t *p)
{
	dtrace_hdl_t *dtp = p->dtpq_hdl;

	dt_free(dtp, p->dtpq_items);
	dt_free(dtp, p);
}