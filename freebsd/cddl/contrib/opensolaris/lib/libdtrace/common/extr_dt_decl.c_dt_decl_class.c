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
struct TYPE_3__ {scalar_t__ ds_class; } ;
typedef  TYPE_1__ dt_scope_t ;
typedef  scalar_t__ dt_dclass_t ;
struct TYPE_4__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ DT_DC_DEFAULT ; 
 int /*<<< orphan*/  D_DECL_CLASS ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* yypcb ; 

void
dt_decl_class(dt_dclass_t class)
{
	dt_scope_t *dsp = &yypcb->pcb_dstack;

	if (dsp->ds_class != DT_DC_DEFAULT) {
		xyerror(D_DECL_CLASS, "only one storage class allowed "
		    "in a declaration\n");
	}

	dsp->ds_class = class;
}