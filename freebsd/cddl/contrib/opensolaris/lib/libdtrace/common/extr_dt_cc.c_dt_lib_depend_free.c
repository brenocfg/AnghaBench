#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dt_lib_dep_sorted; int /*<<< orphan*/  dt_lib_dep; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_9__ {struct TYPE_9__* dtld_library; struct TYPE_9__* dtld_libpath; int /*<<< orphan*/  dtld_dependents; int /*<<< orphan*/  dtld_dependencies; } ;
typedef  TYPE_2__ dt_lib_depend_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_list_delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* dt_list_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_lib_depend_free(dtrace_hdl_t *dtp)
{
	dt_lib_depend_t *dld, *dlda;

	while ((dld = dt_list_next(&dtp->dt_lib_dep)) != NULL) {
		while ((dlda = dt_list_next(&dld->dtld_dependencies)) != NULL) {
			dt_list_delete(&dld->dtld_dependencies, dlda);
			dt_free(dtp, dlda->dtld_library);
			dt_free(dtp, dlda->dtld_libpath);
			dt_free(dtp, dlda);
		}
		while ((dlda = dt_list_next(&dld->dtld_dependents)) != NULL) {
			dt_list_delete(&dld->dtld_dependents, dlda);
			dt_free(dtp, dlda->dtld_library);
			dt_free(dtp, dlda->dtld_libpath);
			dt_free(dtp, dlda);
		}
		dt_list_delete(&dtp->dt_lib_dep, dld);
		dt_free(dtp, dld->dtld_library);
		dt_free(dtp, dld->dtld_libpath);
		dt_free(dtp, dld);
	}

	while ((dld = dt_list_next(&dtp->dt_lib_dep_sorted)) != NULL) {
		dt_list_delete(&dtp->dt_lib_dep_sorted, dld);
		dt_free(dtp, dld->dtld_library);
		dt_free(dtp, dld);
	}
}