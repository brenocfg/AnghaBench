#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  tfile ;
struct TYPE_22__ {scalar_t__ dp_dofversion; } ;
typedef  TYPE_1__ dtrace_prog_t ;
struct TYPE_23__ {char const* dt_ld_path; int dt_linktype; int dt_oflags; char const* dt_objcopy_path; int /*<<< orphan*/  dt_lazyload; int /*<<< orphan*/  dt_lib_path; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_24__ {char* dir_path; } ;
typedef  TYPE_3__ dt_dirpath_t ;
typedef  int /*<<< orphan*/  drti ;
struct TYPE_25__ {int /*<<< orphan*/  dofh_filesz; } ;
typedef  TYPE_4__ dof_hdr_t ;

/* Variables and functions */
 scalar_t__ DOF_VERSION_2 ; 
 int DTRACE_O_LP64 ; 
#define  DT_LTYP_DOF 129 
#define  DT_LTYP_ELF 128 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WTERMSIG (int) ; 
 char* _dtrace_libdir ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dt_link_error (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* dt_list_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_write (TYPE_2__*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* dtrace_dof_create (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_dof_destroy (TYPE_2__*,TYPE_4__*) ; 
 int dtrace_errno (TYPE_2__*) ; 
 int dump_elf32 (TYPE_2__*,TYPE_4__*,int) ; 
 int dump_elf64 (TYPE_2__*,TYPE_4__*,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkostemp (char*,int /*<<< orphan*/ ) ; 
 int open64 (char const*,int,int) ; 
 scalar_t__ process_obj (TYPE_2__*,char* const,int*) ; 
 scalar_t__ rename (char*,char const*) ; 
 int snprintf (char*,size_t,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char* const,char const*) ; 
 scalar_t__ strerror (int) ; 
 scalar_t__ strlen (char* const) ; 
 int system (char*) ; 
 int /*<<< orphan*/  unlink (char* const) ; 

int
dtrace_program_link(dtrace_hdl_t *dtp, dtrace_prog_t *pgp, uint_t dflags,
    const char *file, int objc, char *const objv[])
{
#ifndef illumos
	char tfile[PATH_MAX];
#endif
	char drti[PATH_MAX];
	dof_hdr_t *dof;
	int fd, status, i, cur;
	char *cmd, tmp;
	size_t len;
	int eprobes = 0, ret = 0;

#ifndef illumos
	if (access(file, R_OK) == 0) {
		fprintf(stderr, "dtrace: target object (%s) already exists. "
		    "Please remove the target\ndtrace: object and rebuild all "
		    "the source objects if you wish to run the DTrace\n"
		    "dtrace: linking process again\n", file);
		/*
		 * Several build infrastructures run DTrace twice (e.g.
		 * postgres) and we don't want the build to fail. Return
		 * 0 here since this isn't really a fatal error.
		 */
		return (0);
	}
#endif

	/*
	 * A NULL program indicates a special use in which we just link
	 * together a bunch of object files specified in objv and then
	 * unlink(2) those object files.
	 */
	if (pgp == NULL) {
		const char *fmt = "%s -o %s -r";

		len = snprintf(&tmp, 1, fmt, dtp->dt_ld_path, file) + 1;

		for (i = 0; i < objc; i++)
			len += strlen(objv[i]) + 1;

		cmd = alloca(len);

		cur = snprintf(cmd, len, fmt, dtp->dt_ld_path, file);

		for (i = 0; i < objc; i++)
			cur += snprintf(cmd + cur, len - cur, " %s", objv[i]);

		if ((status = system(cmd)) == -1) {
			return (dt_link_error(dtp, NULL, -1, NULL,
			    "failed to run %s: %s", dtp->dt_ld_path,
			    strerror(errno)));
		}

		if (WIFSIGNALED(status)) {
			return (dt_link_error(dtp, NULL, -1, NULL,
			    "failed to link %s: %s failed due to signal %d",
			    file, dtp->dt_ld_path, WTERMSIG(status)));
		}

		if (WEXITSTATUS(status) != 0) {
			return (dt_link_error(dtp, NULL, -1, NULL,
			    "failed to link %s: %s exited with status %d\n",
			    file, dtp->dt_ld_path, WEXITSTATUS(status)));
		}

		for (i = 0; i < objc; i++) {
			if (strcmp(objv[i], file) != 0)
				(void) unlink(objv[i]);
		}

		return (0);
	}

	for (i = 0; i < objc; i++) {
		if (process_obj(dtp, objv[i], &eprobes) != 0)
			return (-1); /* errno is set for us */
	}

	/*
	 * If there are is-enabled probes then we need to force use of DOF
	 * version 2.
	 */
	if (eprobes && pgp->dp_dofversion < DOF_VERSION_2)
		pgp->dp_dofversion = DOF_VERSION_2;

	if ((dof = dtrace_dof_create(dtp, pgp, dflags)) == NULL)
		return (-1); /* errno is set for us */

#ifdef illumos
	/*
	 * Create a temporary file and then unlink it if we're going to
	 * combine it with drti.o later.  We can still refer to it in child
	 * processes as /dev/fd/<fd>.
	 */
	if ((fd = open64(file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1) {
		return (dt_link_error(dtp, NULL, -1, NULL,
		    "failed to open %s: %s", file, strerror(errno)));
	}
#else
	snprintf(tfile, sizeof(tfile), "%s.XXXXXX", file);
	if ((fd = mkostemp(tfile, O_CLOEXEC)) == -1)
		return (dt_link_error(dtp, NULL, -1, NULL,
		    "failed to create temporary file %s: %s",
		    tfile, strerror(errno)));
#endif

	/*
	 * If -xlinktype=DOF has been selected, just write out the DOF.
	 * Otherwise proceed to the default of generating and linking ELF.
	 */
	switch (dtp->dt_linktype) {
	case DT_LTYP_DOF:
		if (dt_write(dtp, fd, dof, dof->dofh_filesz) < dof->dofh_filesz)
			ret = errno;

		if (close(fd) != 0 && ret == 0)
			ret = errno;

		if (ret != 0) {
			return (dt_link_error(dtp, NULL, -1, NULL,
			    "failed to write %s: %s", file, strerror(ret)));
		}

		return (0);

	case DT_LTYP_ELF:
		break; /* fall through to the rest of dtrace_program_link() */

	default:
		return (dt_link_error(dtp, NULL, -1, NULL,
		    "invalid link type %u\n", dtp->dt_linktype));
	}


#ifdef illumos
	if (!dtp->dt_lazyload)
		(void) unlink(file);
#endif

	if (dtp->dt_oflags & DTRACE_O_LP64)
		status = dump_elf64(dtp, dof, fd);
	else
		status = dump_elf32(dtp, dof, fd);

#ifdef illumos
	if (status != 0 || lseek(fd, 0, SEEK_SET) != 0) {
		return (dt_link_error(dtp, NULL, -1, NULL,
		    "failed to write %s: %s", file, strerror(errno)));
	}
#else
	if (status != 0)
		return (dt_link_error(dtp, NULL, -1, NULL,
		    "failed to write %s: %s", tfile,
		    strerror(dtrace_errno(dtp))));
#endif

	if (!dtp->dt_lazyload) {
#ifdef illumos
		const char *fmt = "%s -o %s -r -Blocal -Breduce /dev/fd/%d %s";

		if (dtp->dt_oflags & DTRACE_O_LP64) {
			(void) snprintf(drti, sizeof (drti),
			    "%s/64/drti.o", _dtrace_libdir);
		} else {
			(void) snprintf(drti, sizeof (drti),
			    "%s/drti.o", _dtrace_libdir);
		}

		len = snprintf(&tmp, 1, fmt, dtp->dt_ld_path, file, fd,
		    drti) + 1;

		cmd = alloca(len);

		(void) snprintf(cmd, len, fmt, dtp->dt_ld_path, file, fd, drti);
#else
		const char *fmt = "%s -o %s -r %s %s";
		dt_dirpath_t *dp = dt_list_next(&dtp->dt_lib_path);

		(void) snprintf(drti, sizeof (drti), "%s/drti.o", dp->dir_path);

		len = snprintf(&tmp, 1, fmt, dtp->dt_ld_path, file, tfile,
		    drti) + 1;

		cmd = alloca(len);

		(void) snprintf(cmd, len, fmt, dtp->dt_ld_path, file, tfile,
		    drti);
#endif
		if ((status = system(cmd)) == -1) {
			ret = dt_link_error(dtp, NULL, fd, NULL,
			    "failed to run %s: %s", dtp->dt_ld_path,
			    strerror(errno));
			goto done;
		}

		if (WIFSIGNALED(status)) {
			ret = dt_link_error(dtp, NULL, fd, NULL,
			    "failed to link %s: %s failed due to signal %d",
			    file, dtp->dt_ld_path, WTERMSIG(status));
			goto done;
		}

		if (WEXITSTATUS(status) != 0) {
			ret = dt_link_error(dtp, NULL, fd, NULL,
			    "failed to link %s: %s exited with status %d\n",
			    file, dtp->dt_ld_path, WEXITSTATUS(status));
			goto done;
		}
		(void) close(fd); /* release temporary file */

#ifdef __FreeBSD__
		/*
		 * Now that we've linked drti.o, reduce the global __SUNW_dof
		 * symbol to a local symbol. This is needed to so that multiple
		 * generated object files (for different providers, for
		 * instance) can be linked together. This is accomplished using
		 * the -Blocal flag with Sun's linker, but GNU ld doesn't appear
		 * to have an equivalent option.
		 */
		asprintf(&cmd, "%s --localize-hidden %s", dtp->dt_objcopy_path,
		    file);
		if ((status = system(cmd)) == -1) {
			ret = dt_link_error(dtp, NULL, -1, NULL,
			    "failed to run %s: %s", dtp->dt_objcopy_path,
			    strerror(errno));
			free(cmd);
			goto done;
		}
		free(cmd);

		if (WIFSIGNALED(status)) {
			ret = dt_link_error(dtp, NULL, -1, NULL,
			    "failed to link %s: %s failed due to signal %d",
			    file, dtp->dt_objcopy_path, WTERMSIG(status));
			goto done;
		}

		if (WEXITSTATUS(status) != 0) {
			ret = dt_link_error(dtp, NULL, -1, NULL,
			    "failed to link %s: %s exited with status %d\n",
			    file, dtp->dt_objcopy_path, WEXITSTATUS(status));
			goto done;
		}
#endif
	} else {
#ifdef __FreeBSD__
		if (rename(tfile, file) != 0) {
			ret = dt_link_error(dtp, NULL, fd, NULL,
			    "failed to rename %s to %s: %s", tfile, file,
			    strerror(errno));
			goto done;
		}
#endif
		(void) close(fd);
	}

done:
	dtrace_dof_destroy(dtp, dof);

#ifdef __FreeBSD__
	if (!dtp->dt_lazyload)
		(void) unlink(tfile);
#endif
	return (ret);
}