#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_11__ {TYPE_1__* dt_ints; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_12__ {scalar_t__ dn_value; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_13__ {TYPE_2__* pcb_hdl; } ;
struct TYPE_10__ {scalar_t__ did_limit; int /*<<< orphan*/  did_type; int /*<<< orphan*/  did_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DT_NODE_INT ; 
 int /*<<< orphan*/  DT_TOK_INEG ; 
 int /*<<< orphan*/  DT_TOK_INT ; 
 int /*<<< orphan*/  DT_TOK_IPOS ; 
 int /*<<< orphan*/  D_INT_OFLOW ; 
 TYPE_3__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 TYPE_3__* dt_node_op1 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int yyintdecimal ; 
 int yyintprefix ; 
 unsigned char* yyintsuffix ; 
 TYPE_4__* yypcb ; 

dt_node_t *
dt_node_int(uintmax_t value)
{
	dt_node_t *dnp = dt_node_alloc(DT_NODE_INT);
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	int n = (yyintdecimal | (yyintsuffix[0] == 'u')) + 1;
	int i = 0;

	const char *p;
	char c;

	dnp->dn_op = DT_TOK_INT;
	dnp->dn_value = value;

	for (p = yyintsuffix; (c = *p) != '\0'; p++) {
		if (c == 'U' || c == 'u')
			i += 1;
		else if (c == 'L' || c == 'l')
			i += 2;
	}

	for (; i < sizeof (dtp->dt_ints) / sizeof (dtp->dt_ints[0]); i += n) {
		if (value <= dtp->dt_ints[i].did_limit) {
			dt_node_type_assign(dnp,
			    dtp->dt_ints[i].did_ctfp,
			    dtp->dt_ints[i].did_type, B_FALSE);

			/*
			 * If a prefix character is present in macro text, add
			 * in the corresponding operator node (see dt_lex.l).
			 */
			switch (yyintprefix) {
			case '+':
				return (dt_node_op1(DT_TOK_IPOS, dnp));
			case '-':
				return (dt_node_op1(DT_TOK_INEG, dnp));
			default:
				return (dnp);
			}
		}
	}

	xyerror(D_INT_OFLOW, "integer constant 0x%llx cannot be represented "
	    "in any built-in integral type\n", (u_longlong_t)value);
	/*NOTREACHED*/
	return (NULL);		/* keep gcc happy */
}