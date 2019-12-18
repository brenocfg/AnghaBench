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
struct TYPE_6__ {int /*<<< orphan*/  dt_lib_path; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_7__ {char* dir_path; } ;
typedef  TYPE_2__ dt_dirpath_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_2__* dt_list_next (int /*<<< orphan*/ *) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
dt_opt_syslibdir(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dt_dirpath_t *dp = dt_list_next(&dtp->dt_lib_path);
	char *path;

	if (arg == NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if ((path = strdup(arg)) == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	free(dp->dir_path);
	dp->dir_path = path;

	return (0);
}