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
struct TYPE_5__ {scalar_t__ dt_gen; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_6__ {scalar_t__ di_gen; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_idhash_delete (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
dt_pcb_pop_ident(dt_idhash_t *dhp, dt_ident_t *idp, void *arg)
{
	dtrace_hdl_t *dtp = arg;

	if (idp->di_gen == dtp->dt_gen)
		dt_idhash_delete(dhp, idp);

	return (0);
}