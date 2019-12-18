#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ds_class; char* ds_ident; } ;
typedef  TYPE_1__ dt_scope_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
struct TYPE_4__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ DT_DC_DEFAULT ; 
 scalar_t__ DT_DC_REGISTER ; 
 int /*<<< orphan*/  D_DECL_PARMCLASS ; 
 int /*<<< orphan*/ * dt_decl_pop () ; 
 int /*<<< orphan*/ * dt_decl_top () ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* yypcb ; 

dt_decl_t *
dt_decl_pop_param(char **idp)
{
	dt_scope_t *dsp = &yypcb->pcb_dstack;

	if (dsp->ds_class != DT_DC_DEFAULT && dsp->ds_class != DT_DC_REGISTER) {
		xyerror(D_DECL_PARMCLASS, "inappropriate storage class "
		    "for function or associative array parameter\n");
	}

	if (idp != NULL && dt_decl_top() != NULL) {
		*idp = dsp->ds_ident;
		dsp->ds_ident = NULL;
	}

	return (dt_decl_pop());
}