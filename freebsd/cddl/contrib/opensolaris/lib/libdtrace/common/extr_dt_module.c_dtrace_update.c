#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char kld_file_stat ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  k_stat ;
struct TYPE_7__ {int dt_oflags; int /*<<< orphan*/ * dt_exec; int /*<<< orphan*/  dt_modlist; int /*<<< orphan*/ * dt_ddefs; int /*<<< orphan*/ * dt_cdefs; int /*<<< orphan*/ * dt_rtld; int /*<<< orphan*/  dt_macros; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_module_t ;
struct TYPE_8__ {int /*<<< orphan*/  di_id; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DTRACE_O_NOSYS ; 
 int /*<<< orphan*/  OBJFS_ROOT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 TYPE_6__* dt_idhash_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dt_list_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_list_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* dt_module_lookup_by_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dt_module_unload (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_module_update (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getpgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  getprojid () ; 
 int /*<<< orphan*/  getsid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettaskid () ; 
 int /*<<< orphan*/  getuid () ; 
 int kldnext (int) ; 
 scalar_t__ kldstat (int,char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

void
dtrace_update(dtrace_hdl_t *dtp)
{
	dt_module_t *dmp;
	DIR *dirp;
#if defined(__FreeBSD__)
	int fileid;
#endif

	for (dmp = dt_list_next(&dtp->dt_modlist);
	    dmp != NULL; dmp = dt_list_next(dmp))
		dt_module_unload(dtp, dmp);

#ifdef illumos
	/*
	 * Open /system/object and attempt to create a libdtrace module for
	 * each kernel module that is loaded on the current system.
	 */
	if (!(dtp->dt_oflags & DTRACE_O_NOSYS) &&
	    (dirp = opendir(OBJFS_ROOT)) != NULL) {
		struct dirent *dp;

		while ((dp = readdir(dirp)) != NULL) {
			if (dp->d_name[0] != '.')
				dt_module_update(dtp, dp->d_name);
		}

		(void) closedir(dirp);
	}
#elif defined(__FreeBSD__)
	/*
	 * Use FreeBSD's kernel loader interface to discover what kernel
	 * modules are loaded and create a libdtrace module for each one.
	 */
	for (fileid = kldnext(0); fileid > 0; fileid = kldnext(fileid)) {
		struct kld_file_stat k_stat;
		k_stat.version = sizeof(k_stat);
		if (kldstat(fileid, &k_stat) == 0)
			dt_module_update(dtp, &k_stat);
	}
#endif

	/*
	 * Look up all the macro identifiers and set di_id to the latest value.
	 * This code collaborates with dt_lex.l on the use of di_id.  We will
	 * need to implement something fancier if we need to support non-ints.
	 */
	dt_idhash_lookup(dtp->dt_macros, "egid")->di_id = getegid();
	dt_idhash_lookup(dtp->dt_macros, "euid")->di_id = geteuid();
	dt_idhash_lookup(dtp->dt_macros, "gid")->di_id = getgid();
	dt_idhash_lookup(dtp->dt_macros, "pid")->di_id = getpid();
	dt_idhash_lookup(dtp->dt_macros, "pgid")->di_id = getpgid(0);
	dt_idhash_lookup(dtp->dt_macros, "ppid")->di_id = getppid();
#ifdef illumos
	dt_idhash_lookup(dtp->dt_macros, "projid")->di_id = getprojid();
#endif
	dt_idhash_lookup(dtp->dt_macros, "sid")->di_id = getsid(0);
#ifdef illumos
	dt_idhash_lookup(dtp->dt_macros, "taskid")->di_id = gettaskid();
#endif
	dt_idhash_lookup(dtp->dt_macros, "uid")->di_id = getuid();

	/*
	 * Cache the pointers to the modules representing the base executable
	 * and the run-time linker in the dtrace client handle. Note that on
	 * x86 krtld is folded into unix, so if we don't find it, use unix
	 * instead.
	 */
	dtp->dt_exec = dt_module_lookup_by_name(dtp, "genunix");
	dtp->dt_rtld = dt_module_lookup_by_name(dtp, "krtld");
	if (dtp->dt_rtld == NULL)
		dtp->dt_rtld = dt_module_lookup_by_name(dtp, "unix");

	/*
	 * If this is the first time we are initializing the module list,
	 * remove the module for genunix from the module list and then move it
	 * to the front of the module list.  We do this so that type and symbol
	 * queries encounter genunix and thereby optimize for the common case
	 * in dtrace_lookup_by_name() and dtrace_lookup_by_type(), below.
	 */
	if (dtp->dt_exec != NULL &&
	    dtp->dt_cdefs == NULL && dtp->dt_ddefs == NULL) {
		dt_list_delete(&dtp->dt_modlist, dtp->dt_exec);
		dt_list_prepend(&dtp->dt_modlist, dtp->dt_exec);
	}
}