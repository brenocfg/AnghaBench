#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ds_decl; int /*<<< orphan*/  ds_enumval; int /*<<< orphan*/  ds_class; int /*<<< orphan*/  ds_type; int /*<<< orphan*/ * ds_ctfp; struct TYPE_4__* ds_ident; struct TYPE_4__* ds_next; } ;
typedef  TYPE_1__ dt_scope_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
struct TYPE_5__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  EDT_NOSCOPE ; 
 int /*<<< orphan*/  ctf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_decl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

dt_decl_t *
dt_scope_pop(void)
{
	dt_scope_t *rsp = &yypcb->pcb_dstack;
	dt_scope_t *dsp = rsp->ds_next;

	if (dsp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOSCOPE);

	if (dsp->ds_ctfp != NULL && ctf_update(dsp->ds_ctfp) == CTF_ERR) {
		xyerror(D_UNKNOWN, "failed to update type definitions: %s\n",
		    ctf_errmsg(ctf_errno(dsp->ds_ctfp)));
	}

	dt_decl_free(rsp->ds_decl);
	free(rsp->ds_ident);

	rsp->ds_decl = dsp->ds_decl;
	rsp->ds_next = dsp->ds_next;
	rsp->ds_ident = dsp->ds_ident;
	rsp->ds_ctfp = dsp->ds_ctfp;
	rsp->ds_type = dsp->ds_type;
	rsp->ds_class = dsp->ds_class;
	rsp->ds_enumval = dsp->ds_enumval;

	free(dsp);
	return (rsp->ds_decl);
}