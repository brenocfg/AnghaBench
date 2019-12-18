#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_attribute_t ;
struct TYPE_12__ {int /*<<< orphan*/  dn_flags; struct TYPE_12__* dn_list; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_13__ {int di_flags; int /*<<< orphan*/  di_attr; TYPE_1__* di_ops; } ;
typedef  TYPE_3__ dt_ident_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* di_cook ) (TYPE_2__*,TYPE_3__*,int,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DT_IDFLG_REF ; 
 int DT_IDFLG_USER ; 
 int /*<<< orphan*/  DT_NF_USERLAND ; 
 int /*<<< orphan*/  dt_attr_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_list_cook (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*,int,TYPE_2__*) ; 

dtrace_attribute_t
dt_ident_cook(dt_node_t *dnp, dt_ident_t *idp, dt_node_t **pargp)
{
	dtrace_attribute_t attr;
	dt_node_t *args, *argp;
	int argc = 0;

	attr = dt_node_list_cook(pargp, DT_IDFLG_REF);
	args = pargp ? *pargp : NULL;

	for (argp = args; argp != NULL; argp = argp->dn_list)
		argc++;

	idp->di_ops->di_cook(dnp, idp, argc, args);

	if (idp->di_flags & DT_IDFLG_USER)
		dnp->dn_flags |= DT_NF_USERLAND;

	return (dt_attr_min(attr, idp->di_attr));
}