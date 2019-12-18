#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ di_gen; int di_flags; } ;
typedef  TYPE_2__ dt_ident_t ;
struct TYPE_7__ {TYPE_1__* pcb_hdl; } ;
struct TYPE_5__ {scalar_t__ dt_gen; } ;

/* Variables and functions */
 int DT_IDFLG_DECL ; 
 int DT_IDFLG_MOD ; 
 int DT_IDFLG_REF ; 
 TYPE_3__* yypcb ; 

int
dt_ident_unref(const dt_ident_t *idp)
{
	return (idp->di_gen == yypcb->pcb_hdl->dt_gen &&
	    (idp->di_flags & (DT_IDFLG_REF|DT_IDFLG_MOD|DT_IDFLG_DECL)) == 0);
}