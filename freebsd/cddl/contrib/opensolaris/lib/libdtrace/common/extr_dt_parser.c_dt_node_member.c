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
struct TYPE_9__ {int /*<<< orphan*/  dtt_flags; int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_10__ {char* dn_membname; struct TYPE_10__* dn_membexpr; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
struct TYPE_11__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NODE_MEMBER ; 
 int /*<<< orphan*/  EDT_COMPILER ; 
 int /*<<< orphan*/  dt_decl_free (int /*<<< orphan*/ *) ; 
 int dt_decl_type (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

dt_node_t *
dt_node_member(dt_decl_t *ddp, char *name, dt_node_t *expr)
{
	dtrace_typeinfo_t dtt;
	dt_node_t *dnp;
	int err;

	if (ddp != NULL) {
		err = dt_decl_type(ddp, &dtt);
		dt_decl_free(ddp);

		if (err != 0)
			longjmp(yypcb->pcb_jmpbuf, EDT_COMPILER);
	}

	dnp = dt_node_alloc(DT_NODE_MEMBER);
	dnp->dn_membname = name;
	dnp->dn_membexpr = expr;

	if (ddp != NULL)
		dt_node_type_assign(dnp, dtt.dtt_ctfp, dtt.dtt_type,
		    dtt.dtt_flags);

	return (dnp);
}