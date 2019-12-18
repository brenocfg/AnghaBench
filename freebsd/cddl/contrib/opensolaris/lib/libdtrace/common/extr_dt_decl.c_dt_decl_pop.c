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
struct TYPE_3__ {int ds_enumval; int /*<<< orphan*/  ds_class; int /*<<< orphan*/  ds_type; int /*<<< orphan*/ * ds_ctfp; int /*<<< orphan*/ * ds_ident; int /*<<< orphan*/ * ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
struct TYPE_4__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  DT_DC_DEFAULT ; 
 int /*<<< orphan*/ * dt_decl_top () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__* yypcb ; 

dt_decl_t *
dt_decl_pop(void)
{
	dt_scope_t *dsp = &yypcb->pcb_dstack;
	dt_decl_t *ddp = dt_decl_top();

	dsp->ds_decl = NULL;
	free(dsp->ds_ident);
	dsp->ds_ident = NULL;
	dsp->ds_ctfp = NULL;
	dsp->ds_type = CTF_ERR;
	dsp->ds_class = DT_DC_DEFAULT;
	dsp->ds_enumval = -1;

	return (ddp);
}