#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;
struct TYPE_8__ {scalar_t__ dd_kind; struct TYPE_8__* dd_next; int /*<<< orphan*/ * dd_name; } ;
typedef  TYPE_2__ dt_decl_t ;
struct TYPE_9__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ CTF_K_UNKNOWN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_decl_check (TYPE_2__*) ; 
 TYPE_3__* yypcb ; 

dt_decl_t *
dt_decl_push(dt_decl_t *ddp)
{
	dt_scope_t *dsp = &yypcb->pcb_dstack;
	dt_decl_t *top = dsp->ds_decl;

	if (top != NULL &&
	    top->dd_kind == CTF_K_UNKNOWN && top->dd_name == NULL) {
		top->dd_kind = CTF_K_INTEGER;
		(void) dt_decl_check(top);
	}

	assert(ddp->dd_next == NULL);
	ddp->dd_next = top;
	dsp->ds_decl = ddp;

	return (ddp);
}