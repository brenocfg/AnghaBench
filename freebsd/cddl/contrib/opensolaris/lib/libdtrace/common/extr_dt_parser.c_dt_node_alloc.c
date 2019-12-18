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
struct TYPE_5__ {struct TYPE_5__* dn_link; int /*<<< orphan*/  dn_line; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_6__ {TYPE_1__* pcb_list; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/  pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_1__* dt_node_xalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylineno ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static dt_node_t *
dt_node_alloc(int kind)
{
	dt_node_t *dnp = dt_node_xalloc(yypcb->pcb_hdl, kind);

	if (dnp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dnp->dn_line = yylineno;
	dnp->dn_link = yypcb->pcb_list;
	yypcb->pcb_list = dnp;

	return (dnp);
}