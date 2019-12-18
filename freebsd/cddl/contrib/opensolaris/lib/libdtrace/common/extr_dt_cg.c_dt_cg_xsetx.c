#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {TYPE_1__* dl_last; } ;
typedef  TYPE_2__ dt_irlist_t ;
typedef  int /*<<< orphan*/  dt_ident_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_8__ {int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/  pcb_inttab; } ;
struct TYPE_6__ {int /*<<< orphan*/ * di_extern; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_SETX (int /*<<< orphan*/ ,int) ; 
 int DIF_INTOFF_MAX ; 
 int DT_INT_PRIVATE ; 
 int DT_INT_SHARED ; 
 int /*<<< orphan*/  EDT_INT2BIG ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dt_inttab_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt_irlist_append (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

__attribute__((used)) static void
dt_cg_xsetx(dt_irlist_t *dlp, dt_ident_t *idp, uint_t lbl, int reg, uint64_t x)
{
	int flag = idp != NULL ? DT_INT_PRIVATE : DT_INT_SHARED;
	int intoff = dt_inttab_insert(yypcb->pcb_inttab, x, flag);
	dif_instr_t instr = DIF_INSTR_SETX((uint_t)intoff, reg);

	if (intoff == -1)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	if (intoff > DIF_INTOFF_MAX)
		longjmp(yypcb->pcb_jmpbuf, EDT_INT2BIG);

	dt_irlist_append(dlp, dt_cg_node_alloc(lbl, instr));

	if (idp != NULL)
		dlp->dl_last->di_extern = idp;
}