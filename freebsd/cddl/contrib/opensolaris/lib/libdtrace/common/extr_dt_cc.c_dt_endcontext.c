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
struct TYPE_6__ {int /*<<< orphan*/  dt_globals; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_7__ {int /*<<< orphan*/  di_attr; } ;
typedef  TYPE_2__ dt_ident_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pcb_probe; int /*<<< orphan*/ * pcb_pdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dtrace_defattr ; 
 TYPE_2__* dt_idhash_lookup (int /*<<< orphan*/ ,char const* const) ; 
 TYPE_3__* yypcb ; 

void
dt_endcontext(dtrace_hdl_t *dtp)
{
	static const char *const cvars[] = {
		"probeprov", "probemod", "probefunc", "probename", "args", NULL
	};

	dt_ident_t *idp;
	int i;

	for (i = 0; cvars[i] != NULL; i++) {
		if ((idp = dt_idhash_lookup(dtp->dt_globals, cvars[i])) != NULL)
			idp->di_attr = _dtrace_defattr;
	}

	yypcb->pcb_pdesc = NULL;
	yypcb->pcb_probe = NULL;
}