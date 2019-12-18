#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ps_prochandle {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dt_vector; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_10__ {int /*<<< orphan*/  st_value; } ;
typedef  TYPE_2__ GElf_Sym ;

/* Variables and functions */
 int PGRAB_FORCE ; 
 int PGRAB_RDONLY ; 
 scalar_t__ Plookup_by_addr (struct ps_prochandle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct ps_prochandle* dt_proc_grab (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_proc_lock (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_release (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_unlock (TYPE_1__*,struct ps_prochandle*) ; 

__attribute__((used)) static void
dt_aggregate_usym(dtrace_hdl_t *dtp, uint64_t *data)
{
	uint64_t pid = data[0];
	uint64_t *pc = &data[1];
	struct ps_prochandle *P;
	GElf_Sym sym;

	if (dtp->dt_vector != NULL)
		return;

	if ((P = dt_proc_grab(dtp, pid, PGRAB_RDONLY | PGRAB_FORCE, 0)) == NULL)
		return;

	dt_proc_lock(dtp, P);

	if (Plookup_by_addr(P, *pc, NULL, 0, &sym) == 0)
		*pc = sym.st_value;

	dt_proc_unlock(dtp, P);
	dt_proc_release(dtp, P);
}