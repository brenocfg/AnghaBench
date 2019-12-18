#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_6__ {char* dn_string; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DT_NODE_STRING ; 
 int /*<<< orphan*/  DT_STR_CTFP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DT_STR_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DT_TOK_STRING ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

dt_node_t *
dt_node_string(char *string)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dt_node_t *dnp;

	if (string == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dnp = dt_node_alloc(DT_NODE_STRING);
	dnp->dn_op = DT_TOK_STRING;
	dnp->dn_string = string;
	dt_node_type_assign(dnp, DT_STR_CTFP(dtp), DT_STR_TYPE(dtp), B_FALSE);

	return (dnp);
}