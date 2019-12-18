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
struct TYPE_5__ {struct TYPE_5__* ds_next; int /*<<< orphan*/  ds_enumval; int /*<<< orphan*/  ds_class; int /*<<< orphan*/  ds_type; int /*<<< orphan*/ * ds_ctfp; int /*<<< orphan*/  ds_ident; int /*<<< orphan*/  ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_6__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  dt_scope_create (TYPE_1__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_2__* yypcb ; 

void
dt_scope_push(ctf_file_t *ctfp, ctf_id_t type)
{
	dt_scope_t *rsp = &yypcb->pcb_dstack;
	dt_scope_t *dsp = malloc(sizeof (dt_scope_t));

	if (dsp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dsp->ds_decl = rsp->ds_decl;
	dsp->ds_next = rsp->ds_next;
	dsp->ds_ident = rsp->ds_ident;
	dsp->ds_ctfp = ctfp;
	dsp->ds_type = type;
	dsp->ds_class = rsp->ds_class;
	dsp->ds_enumval = rsp->ds_enumval;

	dt_scope_create(rsp);
	rsp->ds_next = dsp;
}