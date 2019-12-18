#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  int_hdl; struct TYPE_5__* int_hash; struct TYPE_5__* inh_next; struct TYPE_5__* int_head; } ;
typedef  TYPE_1__ dt_inttab_t ;
typedef  TYPE_1__ dt_inthash_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
dt_inttab_destroy(dt_inttab_t *ip)
{
	dt_inthash_t *hp, *np;

	for (hp = ip->int_head; hp != NULL; hp = np) {
		np = hp->inh_next;
		dt_free(ip->int_hdl, hp);
	}

	dt_free(ip->int_hdl, ip->int_hash);
	dt_free(ip->int_hdl, ip);
}