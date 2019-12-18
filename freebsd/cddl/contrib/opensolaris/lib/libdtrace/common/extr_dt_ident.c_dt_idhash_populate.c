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
struct TYPE_6__ {int /*<<< orphan*/  dh_name; TYPE_2__* dh_tmpl; } ;
typedef  TYPE_1__ dt_idhash_t ;
struct TYPE_7__ {int /*<<< orphan*/  di_iarg; int /*<<< orphan*/ * di_ops; int /*<<< orphan*/  di_vers; int /*<<< orphan*/  di_attr; int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_flags; int /*<<< orphan*/  di_kind; int /*<<< orphan*/ * di_name; } ;
typedef  TYPE_2__ dt_ident_t ;
struct TYPE_8__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * dt_idhash_insert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_idops_thaw ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

__attribute__((used)) static void
dt_idhash_populate(dt_idhash_t *dhp)
{
	const dt_ident_t *idp = dhp->dh_tmpl;

	dhp->dh_tmpl = NULL; /* clear dh_tmpl first to avoid recursion */
	dt_dprintf("populating %s idhash from %p\n", dhp->dh_name, (void *)idp);

	for (; idp->di_name != NULL; idp++) {
		if (dt_idhash_insert(dhp, idp->di_name,
		    idp->di_kind, idp->di_flags, idp->di_id, idp->di_attr,
		    idp->di_vers, idp->di_ops ? idp->di_ops : &dt_idops_thaw,
		    idp->di_iarg, 0) == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);
	}
}