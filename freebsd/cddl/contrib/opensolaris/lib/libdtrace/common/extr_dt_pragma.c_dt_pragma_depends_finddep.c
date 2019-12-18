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
struct stat {int dummy; } ;
struct TYPE_7__ {char* dir_path; } ;
struct TYPE_6__ {TYPE_2__ dt_lib_path; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_dirpath_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_PRAGMA_DEPEND ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void 
dt_pragma_depends_finddep(dtrace_hdl_t *dtp, const char *lname, char *lib,
    size_t len)
{
	dt_dirpath_t *dirp;
	struct stat sbuf;
	int found = 0;

	for (dirp = dt_list_next(&dtp->dt_lib_path); dirp != NULL;
	    dirp = dt_list_next(dirp)) {
		(void) snprintf(lib, len, "%s/%s", dirp->dir_path, lname);

		if (stat(lib, &sbuf) == 0) {
			found = 1;
			break;
		}
	}

	if (!found)
		xyerror(D_PRAGMA_DEPEND,
		    "failed to find dependency in libpath: %s", lname);
}