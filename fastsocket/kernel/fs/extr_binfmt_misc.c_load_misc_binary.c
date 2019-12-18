#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct linux_binprm {int interp_data; char* interp; int /*<<< orphan*/  interp_flags; int /*<<< orphan*/  buf; struct file* file; int /*<<< orphan*/  argc; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  interpreter; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int BINPRM_BUF_SIZE ; 
 int /*<<< orphan*/  BINPRM_FLAGS_ENFORCE_NONDUMP ; 
 int /*<<< orphan*/  BINPRM_FLAGS_EXECFD ; 
 int ENOEXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  MAY_READ ; 
 int MISC_FMT_CREDENTIALS ; 
 int MISC_FMT_OPEN_BINARY ; 
 int MISC_FMT_PRESERVE_ARGV0 ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int bprm_change_interp (char*,struct linux_binprm*) ; 
 TYPE_1__* check_file (struct linux_binprm*) ; 
 int copy_strings_kernel (int,char**,struct linux_binprm*) ; 
 int /*<<< orphan*/  enabled ; 
 int /*<<< orphan*/  entries_lock ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 scalar_t__ file_permission (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int get_unused_fd () ; 
 int kernel_read (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct file* open_exec (char*) ; 
 int prepare_binprm (struct linux_binprm*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int remove_arg_zero (struct linux_binprm*) ; 
 int search_binary_handler (struct linux_binprm*,struct pt_regs*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sys_close (int) ; 

__attribute__((used)) static int load_misc_binary(struct linux_binprm *bprm, struct pt_regs *regs)
{
	Node *fmt;
	struct file * interp_file = NULL;
	char iname[BINPRM_BUF_SIZE];
	char *iname_addr = iname;
	int retval;
	int fd_binary = -1;

	retval = -ENOEXEC;
	if (!enabled)
		goto _ret;

	/* to keep locking time low, we copy the interpreter string */
	read_lock(&entries_lock);
	fmt = check_file(bprm);
	if (fmt)
		strlcpy(iname, fmt->interpreter, BINPRM_BUF_SIZE);
	read_unlock(&entries_lock);
	if (!fmt)
		goto _ret;

	if (!(fmt->flags & MISC_FMT_PRESERVE_ARGV0)) {
		retval = remove_arg_zero(bprm);
		if (retval)
			goto _ret;
	}

	if (fmt->flags & MISC_FMT_OPEN_BINARY) {

		/* if the binary should be opened on behalf of the
		 * interpreter than keep it open and assign descriptor
		 * to it */
 		fd_binary = get_unused_fd();
 		if (fd_binary < 0) {
 			retval = fd_binary;
 			goto _ret;
 		}
 		fd_install(fd_binary, bprm->file);

		/* if the binary is not readable than enforce mm->dumpable=0
		   regardless of the interpreter's permissions */
		if (file_permission(bprm->file, MAY_READ))
			bprm->interp_flags |= BINPRM_FLAGS_ENFORCE_NONDUMP;

		allow_write_access(bprm->file);
		bprm->file = NULL;

		/* mark the bprm that fd should be passed to interp */
		bprm->interp_flags |= BINPRM_FLAGS_EXECFD;
		bprm->interp_data = fd_binary;

 	} else {
 		allow_write_access(bprm->file);
 		fput(bprm->file);
 		bprm->file = NULL;
 	}
	/* make argv[1] be the path to the binary */
	retval = copy_strings_kernel (1, &bprm->interp, bprm);
	if (retval < 0)
		goto _error;
	bprm->argc++;

	/* add the interp as argv[0] */
	retval = copy_strings_kernel (1, &iname_addr, bprm);
	if (retval < 0)
		goto _error;
	bprm->argc ++;

	/* Update interp in case binfmt_script needs it. */
	retval = bprm_change_interp(iname, bprm);
	if (retval < 0)
		goto _error;

	interp_file = open_exec (iname);
	retval = PTR_ERR (interp_file);
	if (IS_ERR (interp_file))
		goto _error;

	bprm->file = interp_file;
	if (fmt->flags & MISC_FMT_CREDENTIALS) {
		/*
		 * No need to call prepare_binprm(), it's already been
		 * done.  bprm->buf is stale, update from interp_file.
		 */
		memset(bprm->buf, 0, BINPRM_BUF_SIZE);
		retval = kernel_read(bprm->file, 0, bprm->buf, BINPRM_BUF_SIZE);
	} else
		retval = prepare_binprm (bprm);

	if (retval < 0)
		goto _error;

	retval = search_binary_handler (bprm, regs);
	if (retval < 0)
		goto _error;

_ret:
	return retval;
_error:
	if (fd_binary > 0)
		sys_close(fd_binary);
	bprm->interp_flags = 0;
	bprm->interp_data = 0;
	goto _ret;
}