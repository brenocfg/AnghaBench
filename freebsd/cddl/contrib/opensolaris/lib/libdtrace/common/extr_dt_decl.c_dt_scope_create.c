#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ds_enumval; int /*<<< orphan*/  ds_class; int /*<<< orphan*/  ds_type; int /*<<< orphan*/ * ds_ctfp; int /*<<< orphan*/ * ds_ident; int /*<<< orphan*/ * ds_next; int /*<<< orphan*/ * ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  DT_DC_DEFAULT ; 

void
dt_scope_create(dt_scope_t *dsp)
{
	dsp->ds_decl = NULL;
	dsp->ds_next = NULL;
	dsp->ds_ident = NULL;
	dsp->ds_ctfp = NULL;
	dsp->ds_type = CTF_ERR;
	dsp->ds_class = DT_DC_DEFAULT;
	dsp->ds_enumval = -1;
}