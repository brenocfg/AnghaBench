#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_prog_t ;
struct TYPE_13__ {int /*<<< orphan*/  dtld_loaded; int /*<<< orphan*/ * dtld_library; } ;
struct TYPE_12__ {scalar_t__ dt_errno; scalar_t__ dt_errtag; int /*<<< orphan*/ * dt_filetag; TYPE_2__ dt_lib_dep_sorted; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_lib_depend_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DTRACE_C_EMPTY ; 
 int /*<<< orphan*/  D_PRAGMA_DEPEND ; 
 scalar_t__ EDT_COMPILER ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_errtag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_lib_depend_free (TYPE_1__*) ; 
 int dt_lib_depend_sort (TYPE_1__*) ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 
 int /*<<< orphan*/  dt_program_destroy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_errmsg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (TYPE_1__*) ; 
 int /*<<< orphan*/ * dtrace_program_fcompile (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_load_libs_sort(dtrace_hdl_t *dtp)
{
	dtrace_prog_t *pgp;
	FILE *fp;
	dt_lib_depend_t *dld;

	/*
	 * Finish building the graph containing the library dependencies
	 * and perform a topological sort to generate an ordered list
	 * for compilation.
	 */
	if (dt_lib_depend_sort(dtp) == -1)
		goto err;

	for (dld = dt_list_next(&dtp->dt_lib_dep_sorted); dld != NULL;
	    dld = dt_list_next(dld)) {

		if ((fp = fopen(dld->dtld_library, "r")) == NULL) {
			dt_dprintf("skipping library %s: %s\n",
			    dld->dtld_library, strerror(errno));
			continue;
		}

		dtp->dt_filetag = dld->dtld_library;
		pgp = dtrace_program_fcompile(dtp, fp, DTRACE_C_EMPTY, 0, NULL);
		(void) fclose(fp);
		dtp->dt_filetag = NULL;

		if (pgp == NULL && (dtp->dt_errno != EDT_COMPILER ||
		    dtp->dt_errtag != dt_errtag(D_PRAGMA_DEPEND)))
			goto err;

		if (pgp == NULL) {
			dt_dprintf("skipping library %s: %s\n",
			    dld->dtld_library,
			    dtrace_errmsg(dtp, dtrace_errno(dtp)));
		} else {
			dld->dtld_loaded = B_TRUE;
			dt_program_destroy(dtp, pgp);
		}
	}

	dt_lib_depend_free(dtp);
	return (0);

err:
	dt_lib_depend_free(dtp);
	return (-1); /* preserve dt_errno */
}