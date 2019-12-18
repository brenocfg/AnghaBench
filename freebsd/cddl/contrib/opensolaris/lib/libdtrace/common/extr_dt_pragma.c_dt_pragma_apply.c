#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_6__ {int di_kind; int /*<<< orphan*/  di_vers; int /*<<< orphan*/  di_attr; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_1__ dt_ident_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pcb_pragmas; } ;

/* Variables and functions */
#define  DT_IDENT_PRAGAT 129 
#define  DT_IDENT_PRAGBN 128 
 int /*<<< orphan*/  dt_idhash_delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* dt_idhash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static void
dt_pragma_apply(dt_idhash_t *dhp, dt_ident_t *idp)
{
	dt_idhash_t *php;
	dt_ident_t *pdp;

	if ((php = yypcb->pcb_pragmas) == NULL)
		return; /* no pragmas pending for current compilation pass */

	while ((pdp = dt_idhash_lookup(php, idp->di_name)) != NULL) {
		switch (pdp->di_kind) {
		case DT_IDENT_PRAGAT:
			idp->di_attr = pdp->di_attr;
			break;
		case DT_IDENT_PRAGBN:
			idp->di_vers = pdp->di_vers;
			break;
		}
		dt_idhash_delete(php, pdp);
	}
}