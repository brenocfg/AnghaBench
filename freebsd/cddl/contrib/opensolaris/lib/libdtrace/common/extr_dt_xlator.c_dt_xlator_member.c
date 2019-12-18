#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* dx_members; } ;
typedef  TYPE_1__ dt_xlator_t ;
struct TYPE_6__ {int /*<<< orphan*/  dn_membname; struct TYPE_6__* dn_list; } ;
typedef  TYPE_2__ dt_node_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

dt_node_t *
dt_xlator_member(dt_xlator_t *dxp, const char *name)
{
	dt_node_t *dnp;

	for (dnp = dxp->dx_members; dnp != NULL; dnp = dnp->dn_list) {
		if (strcmp(dnp->dn_membname, name) == 0)
			return (dnp);
	}

	return (NULL);
}