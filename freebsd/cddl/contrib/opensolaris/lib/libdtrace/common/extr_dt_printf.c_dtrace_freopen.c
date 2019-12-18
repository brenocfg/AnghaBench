#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  selfbuf ;
typedef  int /*<<< orphan*/  restorebuf ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
struct TYPE_8__ {char* dt_sprintf_buf; int dt_stdout_fd; int /*<<< orphan*/ * dt_freopen_fp; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_9__ {TYPE_3__* pfv_argv; } ;
typedef  TYPE_2__ dt_pfargv_t ;
struct TYPE_10__ {scalar_t__ pfd_preflen; char* pfd_prefix; } ;
typedef  TYPE_3__ dt_pfargd_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DT_FREOPEN_RESTORE ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int dt_handle_liberr (TYPE_1__*,int /*<<< orphan*/  const*,char*) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_sprintf (TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int dup (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

int
dtrace_freopen(dtrace_hdl_t *dtp, FILE *fp, void *fmtdata,
    const dtrace_probedata_t *data, const dtrace_recdesc_t *recp,
    uint_t nrecs, const void *buf, size_t len)
{
	char selfbuf[40], restorebuf[40], *filename;
	FILE *nfp;
	int rval, errval;
	dt_pfargv_t *pfv = fmtdata;
	dt_pfargd_t *pfd = pfv->pfv_argv;

	rval = dtrace_sprintf(dtp, fp, fmtdata, recp, nrecs, buf, len);

	if (rval == -1 || fp == NULL)
		return (rval);

#ifdef illumos
	if (pfd->pfd_preflen != 0 &&
	    strcmp(pfd->pfd_prefix, DT_FREOPEN_RESTORE) == 0) {
		/*
		 * The only way to have the format string set to the value
		 * DT_FREOPEN_RESTORE is via the empty freopen() string --
		 * denoting that we should restore the old stdout.
		 */
		assert(strcmp(dtp->dt_sprintf_buf, DT_FREOPEN_RESTORE) == 0);

		if (dtp->dt_stdout_fd == -1) {
			/*
			 * We could complain here by generating an error,
			 * but it seems like overkill:  it seems that calling
			 * freopen() to restore stdout when freopen() has
			 * never before been called should just be a no-op,
			 * so we just return in this case.
			 */
			return (rval);
		}

		(void) snprintf(restorebuf, sizeof (restorebuf),
		    "/dev/fd/%d", dtp->dt_stdout_fd);
		filename = restorebuf;
	} else {
		filename = dtp->dt_sprintf_buf;
	}

	/*
	 * freopen(3C) will always close the specified stream and underlying
	 * file descriptor -- even if the specified file can't be opened.
	 * Even for the semantic cesspool that is standard I/O, this is
	 * surprisingly brain-dead behavior:  it means that any failure to
	 * open the specified file destroys the specified stream in the
	 * process -- which is particularly relevant when the specified stream
	 * happens (or rather, happened) to be stdout.  This could be resolved
	 * were there an "fdreopen()" equivalent of freopen() that allowed one
	 * to pass a file descriptor instead of the name of a file, but there
	 * is no such thing.  However, we can effect this ourselves by first
	 * fopen()'ing the desired file, and then (assuming that that works),
	 * freopen()'ing "/dev/fd/[fileno]", where [fileno] is the underlying
	 * file descriptor for the fopen()'d file.  This way, if the fopen()
	 * fails, we can fail the operation without destroying stdout.
	 */
	if ((nfp = fopen(filename, "aF")) == NULL) {
		char *msg = strerror(errno);
		char *faultstr;
		int len = 80;

		len += strlen(msg) + strlen(filename);
		faultstr = alloca(len);

		(void) snprintf(faultstr, len, "couldn't freopen() \"%s\": %s",
		    filename, strerror(errno));

		if ((errval = dt_handle_liberr(dtp, data, faultstr)) == 0)
			return (rval);

		return (errval);
	}

	(void) snprintf(selfbuf, sizeof (selfbuf), "/dev/fd/%d", fileno(nfp));

	if (dtp->dt_stdout_fd == -1) {
		/*
		 * If this is the first time that we're calling freopen(),
		 * we're going to stash away the file descriptor for stdout.
		 * We don't expect the dup(2) to fail, so if it does we must
		 * return failure.
		 */
		if ((dtp->dt_stdout_fd = dup(fileno(fp))) == -1) {
			(void) fclose(nfp);
			return (dt_set_errno(dtp, errno));
		}
	}

	if (freopen(selfbuf, "aF", fp) == NULL) {
		(void) fclose(nfp);
		return (dt_set_errno(dtp, errno));
	}

	(void) fclose(nfp);
#else	/* !illumos */
	/*
	 * The 'standard output' (which is not necessarily stdout)
	 * treatment on FreeBSD is implemented differently than on
	 * Solaris because FreeBSD's freopen() will attempt to re-use
	 * the current file descriptor, causing the previous file to
	 * be closed and thereby preventing it from be re-activated
	 * later.
	 *
	 * For FreeBSD we use the concept of setting an output file
	 * pointer in the DTrace handle if a dtrace_freopen() has 
	 * enabled another output file and we leave the caller's
	 * file pointer untouched. If it was actually stdout, then
	 * stdout remains open. If it was another file, then that
	 * file remains open. While a dtrace_freopen() has activated
	 * another file, we keep a pointer to that which we use in
	 * the output functions by preference and only use the caller's
	 * file pointer if no dtrace_freopen() call has been made.
	 *
	 * The check to see if we're re-activating the caller's
	 * output file is much the same as on Solaris.
	 */
	if (pfd->pfd_preflen != 0 &&
	    strcmp(pfd->pfd_prefix, DT_FREOPEN_RESTORE) == 0) {
		/*
		 * The only way to have the format string set to the value
		 * DT_FREOPEN_RESTORE is via the empty freopen() string --
		 * denoting that we should restore the old stdout.
		 */
		assert(strcmp(dtp->dt_sprintf_buf, DT_FREOPEN_RESTORE) == 0);

		if (dtp->dt_freopen_fp == NULL) {
			/*
			 * We could complain here by generating an error,
			 * but it seems like overkill:  it seems that calling
			 * freopen() to restore stdout when freopen() has
			 * never before been called should just be a no-op,
			 * so we just return in this case.
			 */
			return (rval);
		}

		/*
		 * At this point, to re-active the original output file,
		 * on FreeBSD we only code the current file that this
		 * function opened previously.
		 */
		(void) fclose(dtp->dt_freopen_fp);
		dtp->dt_freopen_fp = NULL;

		return (rval);
	}

	if ((nfp = fopen(dtp->dt_sprintf_buf, "a")) == NULL) {
		char *msg = strerror(errno);
		char *faultstr;
		int len = 80;

		len += strlen(msg) + strlen(dtp->dt_sprintf_buf);
		faultstr = alloca(len);

		(void) snprintf(faultstr, len, "couldn't freopen() \"%s\": %s",
		    dtp->dt_sprintf_buf, strerror(errno));

		if ((errval = dt_handle_liberr(dtp, data, faultstr)) == 0)
			return (rval);

		return (errval);
	}

	if (dtp->dt_freopen_fp != NULL)
		(void) fclose(dtp->dt_freopen_fp);

	/* Remember that the output has been redirected to the new file. */
	dtp->dt_freopen_fp = nfp;
#endif	/* illumos */

	return (rval);
}