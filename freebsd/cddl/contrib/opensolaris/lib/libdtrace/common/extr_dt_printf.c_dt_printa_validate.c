#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n2 ;
typedef  int /*<<< orphan*/  n1 ;
struct TYPE_9__ {scalar_t__ dn_kind; struct TYPE_9__* dn_list; TYPE_3__* dn_ident; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_10__ {TYPE_1__* dis_args; } ;
typedef  TYPE_2__ dt_idsig_t ;
struct TYPE_11__ {int /*<<< orphan*/  di_name; scalar_t__ di_data; } ;
typedef  TYPE_3__ dt_ident_t ;

/* Variables and functions */
 scalar_t__ DT_NODE_AGG ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_PRINTA_AGGKEY ; 
 int /*<<< orphan*/  D_PRINTA_AGGPROTO ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_node_is_argcompat (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,...) ; 

void
dt_printa_validate(dt_node_t *lhs, dt_node_t *rhs)
{
	dt_ident_t *lid, *rid;
	dt_node_t *lproto, *rproto;
	int largc, rargc, argn;
	char n1[DT_TYPE_NAMELEN];
	char n2[DT_TYPE_NAMELEN];

	assert(lhs->dn_kind == DT_NODE_AGG);
	assert(rhs->dn_kind == DT_NODE_AGG);

	lid = lhs->dn_ident;
	rid = rhs->dn_ident;

	lproto = ((dt_idsig_t *)lid->di_data)->dis_args;
	rproto = ((dt_idsig_t *)rid->di_data)->dis_args;

	/*
	 * First, get an argument count on each side.  These must match.
	 */
	for (largc = 0; lproto != NULL; lproto = lproto->dn_list)
		largc++;

	for (rargc = 0; rproto != NULL; rproto = rproto->dn_list)
		rargc++;

	if (largc != rargc) {
		xyerror(D_PRINTA_AGGKEY, "printa( ): @%s and @%s do not have "
		    "matching key signatures: @%s has %d key%s, @%s has %d "
		    "key%s", lid->di_name, rid->di_name,
		    lid->di_name, largc, largc == 1 ? "" : "s",
		    rid->di_name, rargc, rargc == 1 ? "" : "s");
	}

	/*
	 * Now iterate over the keys to verify that each type matches.
	 */
	lproto = ((dt_idsig_t *)lid->di_data)->dis_args;
	rproto = ((dt_idsig_t *)rid->di_data)->dis_args;

	for (argn = 1; lproto != NULL; argn++, lproto = lproto->dn_list,
	    rproto = rproto->dn_list) {
		assert(rproto != NULL);

		if (dt_node_is_argcompat(lproto, rproto))
			continue;

		xyerror(D_PRINTA_AGGPROTO, "printa( ): @%s[ ] key #%d is "
		    "incompatible with @%s:\n%9s key #%d: %s\n"
		    "%9s key #%d: %s\n",
		    rid->di_name, argn, lid->di_name, lid->di_name, argn,
		    dt_node_type_name(lproto, n1, sizeof (n1)), rid->di_name,
		    argn, dt_node_type_name(rproto, n2, sizeof (n2)));
	}
}