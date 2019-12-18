#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort_t ;
struct TYPE_9__ {int dd_attr; } ;
typedef  TYPE_2__ dt_decl_t ;
struct TYPE_8__ {TYPE_2__* ds_decl; } ;
struct TYPE_10__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_K_UNKNOWN ; 
 int DT_DA_LONG ; 
 int DT_DA_LONGLONG ; 
 int /*<<< orphan*/  dt_decl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* dt_decl_check (TYPE_2__*) ; 
 TYPE_2__* dt_decl_push (int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

dt_decl_t *
dt_decl_attr(ushort_t attr)
{
	dt_decl_t *ddp = yypcb->pcb_dstack.ds_decl;

	if (ddp == NULL) {
		ddp = dt_decl_push(dt_decl_alloc(CTF_K_UNKNOWN, NULL));
		ddp->dd_attr = attr;
		return (ddp);
	}

	if (attr == DT_DA_LONG && (ddp->dd_attr & DT_DA_LONG)) {
		ddp->dd_attr &= ~DT_DA_LONG;
		attr = DT_DA_LONGLONG;
	}

	ddp->dd_attr |= attr;
	return (dt_decl_check(ddp));
}