#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct ps_prochandle {int dummy; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  objname ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_3__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 int PATH_MAX ; 
 int PGRAB_FORCE ; 
 int PGRAB_RDONLY ; 
 scalar_t__ Plookup_by_addr (struct ps_prochandle*,scalar_t__,char*,int,TYPE_1__*) ; 
 scalar_t__ Pobjname (struct ps_prochandle*,scalar_t__,char*,int) ; 
 char* dt_basename (char*) ; 
 struct ps_prochandle* dt_proc_grab (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_proc_lock (int /*<<< orphan*/ *,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_release (int /*<<< orphan*/ *,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_unlock (int /*<<< orphan*/ *,struct ps_prochandle*) ; 
 int dt_string2str (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

int
dtrace_uaddr2str(dtrace_hdl_t *dtp, pid_t pid,
    uint64_t addr, char *str, int nbytes)
{
	char name[PATH_MAX], objname[PATH_MAX], c[PATH_MAX * 2];
	struct ps_prochandle *P = NULL;
	GElf_Sym sym;
	char *obj;

	if (pid != 0)
		P = dt_proc_grab(dtp, pid, PGRAB_RDONLY | PGRAB_FORCE, 0);

	if (P == NULL) {
	  (void) snprintf(c, sizeof (c), "0x%jx", (uintmax_t)addr);
		return (dt_string2str(c, str, nbytes));
	}

	dt_proc_lock(dtp, P);

	if (Plookup_by_addr(P, addr, name, sizeof (name), &sym) == 0) {
		(void) Pobjname(P, addr, objname, sizeof (objname));

		obj = dt_basename(objname);

		if (addr > sym.st_value) {
			(void) snprintf(c, sizeof (c), "%s`%s+0x%llx", obj,
			    name, (u_longlong_t)(addr - sym.st_value));
		} else {
			(void) snprintf(c, sizeof (c), "%s`%s", obj, name);
		}
	} else if (Pobjname(P, addr, objname, sizeof (objname)) != 0) {
		(void) snprintf(c, sizeof (c), "%s`0x%jx",
				dt_basename(objname), (uintmax_t)addr);
	} else {
	  (void) snprintf(c, sizeof (c), "0x%jx", (uintmax_t)addr);
	}

	dt_proc_unlock(dtp, P);
	dt_proc_release(dtp, P);

	return (dt_string2str(c, str, nbytes));
}