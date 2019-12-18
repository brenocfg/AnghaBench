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
struct TYPE_5__ {struct TYPE_5__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */

dt_node_t *
dt_node_link(dt_node_t *lp, dt_node_t *rp)
{
	dt_node_t *dnp;

	if (lp == NULL)
		return (rp);
	else if (rp == NULL)
		return (lp);

	for (dnp = lp; dnp->dn_list != NULL; dnp = dnp->dn_list)
		continue;

	dnp->dn_list = rp;
	return (lp);
}