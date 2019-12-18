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
struct TYPE_9__ {int /*<<< orphan*/  dir_path; } ;
struct TYPE_8__ {int dt_cflags; TYPE_2__ dt_lib_path; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_dirpath_t ;

/* Variables and functions */
 int DTRACE_C_NOLIBS ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 
 scalar_t__ dt_load_libs_dir (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_load_libs_sort (TYPE_1__*) ; 

__attribute__((used)) static int
dt_load_libs(dtrace_hdl_t *dtp)
{
	dt_dirpath_t *dirp;

	if (dtp->dt_cflags & DTRACE_C_NOLIBS)
		return (0); /* libraries already processed */

	dtp->dt_cflags |= DTRACE_C_NOLIBS;

	/*
	 * /usr/lib/dtrace is always at the head of the list. The rest of the
	 * list is specified in the precedence order the user requested. Process
	 * everything other than the head first. DTRACE_C_NOLIBS has already
	 * been spcified so dt_vopen will ensure that there is always one entry
	 * in dt_lib_path.
	 */
	for (dirp = dt_list_next(dt_list_next(&dtp->dt_lib_path));
	    dirp != NULL; dirp = dt_list_next(dirp)) {
		if (dt_load_libs_dir(dtp, dirp->dir_path) != 0) {
			dtp->dt_cflags &= ~DTRACE_C_NOLIBS;
			return (-1); /* errno is set for us */
		}
	}

	/* Handle /usr/lib/dtrace */
	dirp = dt_list_next(&dtp->dt_lib_path);
	if (dt_load_libs_dir(dtp, dirp->dir_path) != 0) {
		dtp->dt_cflags &= ~DTRACE_C_NOLIBS;
		return (-1); /* errno is set for us */
	}

	if (dt_load_libs_sort(dtp) < 0)
		return (-1); /* errno is set for us */

	return (0);
}