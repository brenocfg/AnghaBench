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
struct TYPE_5__ {struct TYPE_5__* ds_next; struct TYPE_5__* ds_ident; int /*<<< orphan*/  ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;
struct TYPE_6__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_decl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_2__* yypcb ; 

void
dt_scope_destroy(dt_scope_t *dsp)
{
	dt_scope_t *nsp;

	for (; dsp != NULL; dsp = nsp) {
		dt_decl_free(dsp->ds_decl);
		free(dsp->ds_ident);
		nsp = dsp->ds_next;
		if (dsp != &yypcb->pcb_dstack)
			free(dsp);
	}
}