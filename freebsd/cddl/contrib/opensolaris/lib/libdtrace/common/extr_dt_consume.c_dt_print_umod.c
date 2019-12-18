#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  char* u_longlong_t ;
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  objname ;
struct TYPE_8__ {int /*<<< orphan*/ * dt_vector; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int PGRAB_FORCE ; 
 int PGRAB_RDONLY ; 
 scalar_t__ Pobjname (struct ps_prochandle*,scalar_t__,char*,int) ; 
 char* dt_basename (char*) ; 
 int dt_printf (TYPE_1__*,int /*<<< orphan*/ *,char const*,char*) ; 
 struct ps_prochandle* dt_proc_grab (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_proc_lock (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_release (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_unlock (TYPE_1__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int
dt_print_umod(dtrace_hdl_t *dtp, FILE *fp, const char *format, caddr_t addr)
{
	/* LINTED - alignment */
	uint64_t pid = ((uint64_t *)addr)[0];
	/* LINTED - alignment */
	uint64_t pc = ((uint64_t *)addr)[1];
	int err = 0;

	char objname[PATH_MAX], c[PATH_MAX * 2];
	struct ps_prochandle *P;

	if (format == NULL)
		format = "  %-50s";

	/*
	 * See the comment in dt_print_ustack() for the rationale for
	 * printing raw addresses in the vectored case.
	 */
	if (dtp->dt_vector == NULL)
		P = dt_proc_grab(dtp, pid, PGRAB_RDONLY | PGRAB_FORCE, 0);
	else
		P = NULL;

	if (P != NULL)
		dt_proc_lock(dtp, P); /* lock handle while we perform lookups */

	if (P != NULL && Pobjname(P, pc, objname, sizeof (objname)) != 0) {
		(void) snprintf(c, sizeof (c), "%s", dt_basename(objname));
	} else {
		(void) snprintf(c, sizeof (c), "0x%llx", (u_longlong_t)pc);
	}

	err = dt_printf(dtp, fp, format, c);

	if (P != NULL) {
		dt_proc_unlock(dtp, P);
		dt_proc_release(dtp, P);
	}

	return (err);
}