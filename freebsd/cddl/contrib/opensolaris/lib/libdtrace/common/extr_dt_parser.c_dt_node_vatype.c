#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dn_attr; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_10__ {TYPE_2__* pcb_hdl; } ;
struct TYPE_8__ {TYPE_1__* dt_cdefs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dm_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  DT_NODE_TYPE ; 
 int /*<<< orphan*/  DT_TOK_IDENT ; 
 int /*<<< orphan*/  _dtrace_defattr ; 
 TYPE_3__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 TYPE_4__* yypcb ; 

dt_node_t *
dt_node_vatype(void)
{
	dt_node_t *dnp = dt_node_alloc(DT_NODE_TYPE);

	dnp->dn_op = DT_TOK_IDENT;
	dnp->dn_ctfp = yypcb->pcb_hdl->dt_cdefs->dm_ctfp;
	dnp->dn_type = CTF_ERR;
	dnp->dn_attr = _dtrace_defattr;

	return (dnp);
}