#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  char const* u_longlong_t ;
struct ps_prochandle {int dummy; } ;
struct TYPE_12__ {int pr_mflags; } ;
typedef  TYPE_1__ prmap_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  objname ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_13__ {scalar_t__* dt_options; int /*<<< orphan*/ * dt_vector; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  char* caddr_t ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_14__ {scalar_t__ st_value; } ;
typedef  TYPE_3__ GElf_Sym ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DTRACEOPT_STACKINDENT ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int DTRACE_USTACK_NFRAMES (scalar_t__) ; 
 int DTRACE_USTACK_STRSIZE (scalar_t__) ; 
 int MA_WRITE ; 
 int PATH_MAX ; 
 int PGRAB_FORCE ; 
 int PGRAB_RDONLY ; 
 TYPE_1__* Paddr_to_map (struct ps_prochandle*,scalar_t__) ; 
 scalar_t__ Plookup_by_addr (struct ps_prochandle*,scalar_t__,char*,int,TYPE_3__*) ; 
 scalar_t__ Pobjname (struct ps_prochandle*,scalar_t__,char*,int) ; 
 int _dtrace_stkindent ; 
 char* dt_basename (char*) ; 
 int dt_printf (TYPE_2__*,int /*<<< orphan*/ *,char const*,...) ; 
 struct ps_prochandle* dt_proc_grab (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_proc_lock (TYPE_2__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_release (TYPE_2__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_proc_unlock (TYPE_2__*,struct ps_prochandle*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 

int
dt_print_ustack(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    caddr_t addr, uint64_t arg)
{
	/* LINTED - alignment */
	uint64_t *pc = (uint64_t *)addr;
	uint32_t depth = DTRACE_USTACK_NFRAMES(arg);
	uint32_t strsize = DTRACE_USTACK_STRSIZE(arg);
	const char *strbase = addr + (depth + 1) * sizeof (uint64_t);
	const char *str = strsize ? strbase : NULL;
	int err = 0;

	char name[PATH_MAX], objname[PATH_MAX], c[PATH_MAX * 2];
	struct ps_prochandle *P;
	GElf_Sym sym;
	int i, indent;
	pid_t pid;

	if (depth == 0)
		return (0);

	pid = (pid_t)*pc++;

	if (dt_printf(dtp, fp, "\n") < 0)
		return (-1);

	if (format == NULL)
		format = "%s";

	if (dtp->dt_options[DTRACEOPT_STACKINDENT] != DTRACEOPT_UNSET)
		indent = (int)dtp->dt_options[DTRACEOPT_STACKINDENT];
	else
		indent = _dtrace_stkindent;

	/*
	 * Ultimately, we need to add an entry point in the library vector for
	 * determining <symbol, offset> from <pid, address>.  For now, if
	 * this is a vector open, we just print the raw address or string.
	 */
	if (dtp->dt_vector == NULL)
		P = dt_proc_grab(dtp, pid, PGRAB_RDONLY | PGRAB_FORCE, 0);
	else
		P = NULL;

	if (P != NULL)
		dt_proc_lock(dtp, P); /* lock handle while we perform lookups */

	for (i = 0; i < depth && pc[i] != 0; i++) {
		const prmap_t *map;

		if ((err = dt_printf(dtp, fp, "%*s", indent, "")) < 0)
			break;

		if (P != NULL && Plookup_by_addr(P, pc[i],
		    name, sizeof (name), &sym) == 0) {
			(void) Pobjname(P, pc[i], objname, sizeof (objname));

			if (pc[i] > sym.st_value) {
				(void) snprintf(c, sizeof (c),
				    "%s`%s+0x%llx", dt_basename(objname), name,
				    (u_longlong_t)(pc[i] - sym.st_value));
			} else {
				(void) snprintf(c, sizeof (c),
				    "%s`%s", dt_basename(objname), name);
			}
		} else if (str != NULL && str[0] != '\0' && str[0] != '@' &&
		    (P != NULL && ((map = Paddr_to_map(P, pc[i])) == NULL ||
		    (map->pr_mflags & MA_WRITE)))) {
			/*
			 * If the current string pointer in the string table
			 * does not point to an empty string _and_ the program
			 * counter falls in a writable region, we'll use the
			 * string from the string table instead of the raw
			 * address.  This last condition is necessary because
			 * some (broken) ustack helpers will return a string
			 * even for a program counter that they can't
			 * identify.  If we have a string for a program
			 * counter that falls in a segment that isn't
			 * writable, we assume that we have fallen into this
			 * case and we refuse to use the string.
			 */
			(void) snprintf(c, sizeof (c), "%s", str);
		} else {
			if (P != NULL && Pobjname(P, pc[i], objname,
			    sizeof (objname)) != 0) {
				(void) snprintf(c, sizeof (c), "%s`0x%llx",
				    dt_basename(objname), (u_longlong_t)pc[i]);
			} else {
				(void) snprintf(c, sizeof (c), "0x%llx",
				    (u_longlong_t)pc[i]);
			}
		}

		if ((err = dt_printf(dtp, fp, format, c)) < 0)
			break;

		if ((err = dt_printf(dtp, fp, "\n")) < 0)
			break;

		if (str != NULL && str[0] == '@') {
			/*
			 * If the first character of the string is an "at" sign,
			 * then the string is inferred to be an annotation --
			 * and it is printed out beneath the frame and offset
			 * with brackets.
			 */
			if ((err = dt_printf(dtp, fp, "%*s", indent, "")) < 0)
				break;

			(void) snprintf(c, sizeof (c), "  [ %s ]", &str[1]);

			if ((err = dt_printf(dtp, fp, format, c)) < 0)
				break;

			if ((err = dt_printf(dtp, fp, "\n")) < 0)
				break;
		}

		if (str != NULL) {
			str += strlen(str) + 1;
			if (str - strbase >= strsize)
				str = NULL;
		}
	}

	if (P != NULL) {
		dt_proc_unlock(dtp, P);
		dt_proc_release(dtp, P);
	}

	return (err);
}