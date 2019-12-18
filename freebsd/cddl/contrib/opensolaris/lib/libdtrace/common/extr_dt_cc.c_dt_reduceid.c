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
struct TYPE_6__ {scalar_t__ dt_vmax; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_7__ {scalar_t__ di_vers; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_idhash_delete (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
dt_reduceid(dt_idhash_t *dhp, dt_ident_t *idp, dtrace_hdl_t *dtp)
{
	if (idp->di_vers != 0 && idp->di_vers > dtp->dt_vmax)
		dt_idhash_delete(dhp, idp);

	return (0);
}