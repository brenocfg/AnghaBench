#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dd_kind; int /*<<< orphan*/ * dd_name; } ;
typedef  TYPE_2__ dt_decl_t ;
struct TYPE_6__ {TYPE_2__* ds_decl; } ;
struct TYPE_8__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ CTF_K_UNKNOWN ; 
 int /*<<< orphan*/  EDT_NODECL ; 
 int /*<<< orphan*/  dt_decl_check (TYPE_2__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

dt_decl_t *
dt_decl_top(void)
{
	dt_decl_t *ddp = yypcb->pcb_dstack.ds_decl;

	if (ddp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NODECL);

	if (ddp->dd_kind == CTF_K_UNKNOWN && ddp->dd_name == NULL) {
		ddp->dd_kind = CTF_K_INTEGER;
		(void) dt_decl_check(ddp);
	}

	return (ddp);
}