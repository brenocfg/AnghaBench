#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ps_prochandle {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dt_vector; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  scalar_t__ dtrace_actkind_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_12__ {int /*<<< orphan*/  st_value; } ;
typedef  TYPE_2__ GElf_Sym ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DTRACEACT_USYM ; 
 int PGRAB_FORCE ; 
 int PGRAB_RDONLY ; 
 scalar_t__ Plookup_by_addr (struct ps_prochandle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* alloca (int) ; 
 int dt_printf (TYPE_1__*,int /*<<< orphan*/ *,char const*,char*) ; 
 struct ps_prochandle* dt_proc_grab (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_proc_lock (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_release (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_unlock (TYPE_1__*,struct ps_prochandle*) ; 
 int dtrace_uaddr2str (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
dt_print_usym(dtrace_hdl_t *dtp, FILE *fp, caddr_t addr, dtrace_actkind_t act)
{
	/* LINTED - alignment */
	uint64_t pid = ((uint64_t *)addr)[0];
	/* LINTED - alignment */
	uint64_t pc = ((uint64_t *)addr)[1];
	const char *format = "  %-50s";
	char *s;
	int n, len = 256;

	if (act == DTRACEACT_USYM && dtp->dt_vector == NULL) {
		struct ps_prochandle *P;

		if ((P = dt_proc_grab(dtp, pid,
		    PGRAB_RDONLY | PGRAB_FORCE, 0)) != NULL) {
			GElf_Sym sym;

			dt_proc_lock(dtp, P);

			if (Plookup_by_addr(P, pc, NULL, 0, &sym) == 0)
				pc = sym.st_value;

			dt_proc_unlock(dtp, P);
			dt_proc_release(dtp, P);
		}
	}

	do {
		n = len;
		s = alloca(n);
	} while ((len = dtrace_uaddr2str(dtp, pid, pc, s, n)) > n);

	return (dt_printf(dtp, fp, format, s));
}