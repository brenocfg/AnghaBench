#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct image_params {char* ip_vdata; int ip_flags; scalar_t__ ip_origcputype; int ip_interp_sugid_fd; char* ip_interp_buffer; scalar_t__ ip_vp; int /*<<< orphan*/  ip_vfs_context; TYPE_1__* ip_origvattr; } ;
struct fileproc {TYPE_2__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {scalar_t__ fg_data; int /*<<< orphan*/ * fg_ops; int /*<<< orphan*/  fg_flag; } ;
struct TYPE_3__ {int va_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  FREAD ; 
 int IMGPF_INTERPRET ; 
 size_t IMG_SHSIZE ; 
 scalar_t__ IS_EOL (char) ; 
 scalar_t__ IS_WHITESPACE (char) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VSGID ; 
 int VSUID ; 
 int /*<<< orphan*/  exec_reset_save_path (struct image_params*) ; 
 int /*<<< orphan*/  exec_save_path (struct image_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int falloc (int /*<<< orphan*/ ,struct fileproc**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sugid_scripts ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_ref (scalar_t__) ; 
 int /*<<< orphan*/  vnops ; 

__attribute__((used)) static int
exec_shell_imgact(struct image_params *imgp)
{
	char *vdata = imgp->ip_vdata;
	char *ihp;
	char *line_startp, *line_endp;
	char *interp;

	/*
	 * Make sure it's a shell script.  If we've already redirected
	 * from an interpreted file once, don't do it again.
	 */
	if (vdata[0] != '#' ||
	    vdata[1] != '!' ||
	    (imgp->ip_flags & IMGPF_INTERPRET) != 0) {
		return (-1);
	}

	if (imgp->ip_origcputype != 0) {
		/* Fat header previously matched, don't allow shell script inside */
		return (-1);
	}

	imgp->ip_flags |= IMGPF_INTERPRET;
	imgp->ip_interp_sugid_fd = -1;
	imgp->ip_interp_buffer[0] = '\0';

	/* Check to see if SUGID scripts are permitted.  If they aren't then
	 * clear the SUGID bits.
	 * imgp->ip_vattr is known to be valid.
	 */
	if (sugid_scripts == 0) {
		imgp->ip_origvattr->va_mode &= ~(VSUID | VSGID);
	}

	/* Try to find the first non-whitespace character */
	for( ihp = &vdata[2]; ihp < &vdata[IMG_SHSIZE]; ihp++ ) {
		if (IS_EOL(*ihp)) {
			/* Did not find interpreter, "#!\n" */
			return (ENOEXEC);
		} else if (IS_WHITESPACE(*ihp)) {
			/* Whitespace, like "#!    /bin/sh\n", keep going. */
		} else {
			/* Found start of interpreter */
			break;
		}
	}

	if (ihp == &vdata[IMG_SHSIZE]) {
		/* All whitespace, like "#!           " */
		return (ENOEXEC);
	}

	line_startp = ihp;

	/* Try to find the end of the interpreter+args string */
	for ( ; ihp < &vdata[IMG_SHSIZE]; ihp++ ) {
		if (IS_EOL(*ihp)) {
			/* Got it */
			break;
		} else {
			/* Still part of interpreter or args */
		}
	}

	if (ihp == &vdata[IMG_SHSIZE]) {
		/* A long line, like "#! blah blah blah" without end */
		return (ENOEXEC);
	}

	/* Backtrack until we find the last non-whitespace */
	while (IS_EOL(*ihp) || IS_WHITESPACE(*ihp)) {
		ihp--;
	}

	/* The character after the last non-whitespace is our logical end of line */
	line_endp = ihp + 1;

	/*
	 * Now we have pointers to the usable part of:
	 *
	 * "#!  /usr/bin/int first    second   third    \n"
	 *      ^ line_startp                       ^ line_endp
	 */

	/* copy the interpreter name */
	interp = imgp->ip_interp_buffer;
	for ( ihp = line_startp; (ihp < line_endp) && !IS_WHITESPACE(*ihp); ihp++)
		*interp++ = *ihp;
	*interp = '\0';

	exec_reset_save_path(imgp);
	exec_save_path(imgp, CAST_USER_ADDR_T(imgp->ip_interp_buffer),
							UIO_SYSSPACE, NULL);

	/* Copy the entire interpreter + args for later processing into argv[] */
	interp = imgp->ip_interp_buffer;
	for ( ihp = line_startp; (ihp < line_endp); ihp++)
		*interp++ = *ihp;
	*interp = '\0';

#if !SECURE_KERNEL
	/*
	 * If we have an SUID or SGID script, create a file descriptor
	 * from the vnode and pass /dev/fd/%d instead of the actual
	 * path name so that the script does not get opened twice
	 */
	if (imgp->ip_origvattr->va_mode & (VSUID | VSGID)) {
		proc_t p;
		struct fileproc *fp;
		int fd;
		int error;

		p = vfs_context_proc(imgp->ip_vfs_context);
		error = falloc(p, &fp, &fd, imgp->ip_vfs_context);
		if (error)
			return(error);

		fp->f_fglob->fg_flag = FREAD;
		fp->f_fglob->fg_ops = &vnops;
		fp->f_fglob->fg_data = (caddr_t)imgp->ip_vp;
		
		proc_fdlock(p);
		procfdtbl_releasefd(p, fd, NULL);
		fp_drop(p, fd, fp, 1);
		proc_fdunlock(p);
		vnode_ref(imgp->ip_vp);

		imgp->ip_interp_sugid_fd = fd;
	}
#endif

	return (-3);
}