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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_12__ {char* dtld_library; } ;
struct TYPE_11__ {char* dt_filetag; scalar_t__ dt_errno; scalar_t__ dt_errtag; TYPE_2__ dt_lib_dep; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_lib_depend_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DTRACE_C_CTL ; 
 int DTRACE_C_EMPTY ; 
 int /*<<< orphan*/  DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  DT_CTX_DPROG ; 
 int /*<<< orphan*/  D_PRAGMA_DEPEND ; 
 scalar_t__ EDT_COMPILER ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 void* dt_compile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_dprintf (char*,char const*,char*) ; 
 scalar_t__ dt_errtag (int /*<<< orphan*/ ) ; 
 scalar_t__ dt_lib_depend_add (TYPE_1__*,TYPE_2__*,char*) ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 
 char* dtrace_errmsg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
dt_load_libs_dir(dtrace_hdl_t *dtp, const char *path)
{
	struct dirent *dp;
	const char *p, *end;
	DIR *dirp;

	char fname[PATH_MAX];
	FILE *fp;
	void *rv;
	dt_lib_depend_t *dld;

	if ((dirp = opendir(path)) == NULL) {
		dt_dprintf("skipping lib dir %s: %s\n", path, strerror(errno));
		return (0);
	}

	/* First, parse each file for library dependencies. */
	while ((dp = readdir(dirp)) != NULL) {
		if ((p = strrchr(dp->d_name, '.')) == NULL || strcmp(p, ".d"))
			continue; /* skip any filename not ending in .d */

		(void) snprintf(fname, sizeof (fname),
		    "%s/%s", path, dp->d_name);

		if ((fp = fopen(fname, "r")) == NULL) {
			dt_dprintf("skipping library %s: %s\n",
			    fname, strerror(errno));
			continue;
		}

		/*
		 * Skip files whose name match an already processed library
		 */
		for (dld = dt_list_next(&dtp->dt_lib_dep); dld != NULL;
		    dld = dt_list_next(dld)) {
			end = strrchr(dld->dtld_library, '/');
			/* dt_lib_depend_add ensures this */
			assert(end != NULL);
			if (strcmp(end + 1, dp->d_name) == 0)
				break;
		}

		if (dld != NULL) {
			dt_dprintf("skipping library %s, already processed "
			    "library with the same name: %s", dp->d_name,
			    dld->dtld_library);
			(void) fclose(fp);
			continue;
		}

		dtp->dt_filetag = fname;
		if (dt_lib_depend_add(dtp, &dtp->dt_lib_dep, fname) != 0) {
			(void) fclose(fp);
			return (-1); /* preserve dt_errno */
		}

		rv = dt_compile(dtp, DT_CTX_DPROG,
		    DTRACE_PROBESPEC_NAME, NULL,
		    DTRACE_C_EMPTY | DTRACE_C_CTL, 0, NULL, fp, NULL);

		if (rv != NULL && dtp->dt_errno &&
		    (dtp->dt_errno != EDT_COMPILER ||
		    dtp->dt_errtag != dt_errtag(D_PRAGMA_DEPEND))) {
			(void) fclose(fp);
			return (-1); /* preserve dt_errno */
		}

		if (dtp->dt_errno)
			dt_dprintf("error parsing library %s: %s\n",
			    fname, dtrace_errmsg(dtp, dtrace_errno(dtp)));

		(void) fclose(fp);
		dtp->dt_filetag = NULL;
	}

	(void) closedir(dirp);

	return (0);
}