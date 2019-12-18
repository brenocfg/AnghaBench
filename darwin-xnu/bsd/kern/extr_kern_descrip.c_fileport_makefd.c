#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct fileproc {struct fileglob* f_fglob; } ;
struct fileport_makefd_args {int /*<<< orphan*/  port; } ;
struct fileglob {int dummy; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct fileproc* FILEPROC_NULL ; 
 scalar_t__ IPC_PORT_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 int /*<<< orphan*/  UF_EXCLOSE ; 
 int fdalloc (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * fdflags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fg_drop (struct fileproc*) ; 
 int /*<<< orphan*/  fg_ref (struct fileproc*) ; 
 struct fileglob* fileport_port_to_fileglob (scalar_t__) ; 
 struct fileproc* fileproc_alloc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileproc_free (struct fileproc*) ; 
 int /*<<< orphan*/  get_task_ipcspace (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_object_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (TYPE_1__*,int,struct fileproc*) ; 

int
fileport_makefd(proc_t p, struct fileport_makefd_args *uap, int32_t *retval)
{
	struct fileglob *fg;
 	struct fileproc *fp = FILEPROC_NULL;
	ipc_port_t port = IPC_PORT_NULL;
	mach_port_name_t send = uap->port;
	kern_return_t res;
	int fd;
	int err;

	res = ipc_object_copyin(get_task_ipcspace(p->task),
			send, MACH_MSG_TYPE_COPY_SEND, &port);

	if (res != KERN_SUCCESS) {
		err = EINVAL;
		goto out;
	}

	fg = fileport_port_to_fileglob(port);
	if (fg == NULL) {
		err = EINVAL;
		goto out;
	}

	fp = fileproc_alloc_init(NULL);
	if (fp == FILEPROC_NULL) {
		err = ENOMEM;
		goto out;
	}

	fp->f_fglob = fg;
	fg_ref(fp);

 	proc_fdlock(p);
	err = fdalloc(p, 0, &fd);
	if (err != 0) {
		proc_fdunlock(p);
		fg_drop(fp);
		goto out;
	}
	*fdflags(p, fd) |= UF_EXCLOSE;

	procfdtbl_releasefd(p, fd, fp);
	proc_fdunlock(p);

	*retval = fd;
	err = 0;
out:
	if ((fp != NULL) && (0 != err)) {
		fileproc_free(fp);
	}

	if (IPC_PORT_NULL != port) {
		ipc_port_release_send(port);
	}

	return err;
}