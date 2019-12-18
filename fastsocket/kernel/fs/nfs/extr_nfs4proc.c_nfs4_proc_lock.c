#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_open_context {struct nfs4_state* state; } ;
struct nfs4_state {int dummy; } ;
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; int fl_type; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOLCK ; 
 int ERESTARTSYS ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  F_GETLK ; 
#define  F_RDLCK 129 
 int F_UNLCK ; 
#define  F_WRLCK 128 
 scalar_t__ IS_GETLK (int) ; 
 scalar_t__ IS_SETLK (int) ; 
 scalar_t__ IS_SETLKW (int) ; 
 unsigned long NFS4_LOCK_MINTIMEOUT ; 
 int nfs4_proc_getlk (struct nfs4_state*,int /*<<< orphan*/ ,struct file_lock*) ; 
 int nfs4_proc_setlk (struct nfs4_state*,int,struct file_lock*) ; 
 int nfs4_proc_unlck (struct nfs4_state*,int,struct file_lock*) ; 
 unsigned long nfs4_set_lock_task_retry (unsigned long) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 scalar_t__ signalled () ; 

__attribute__((used)) static int
nfs4_proc_lock(struct file *filp, int cmd, struct file_lock *request)
{
	struct nfs_open_context *ctx;
	struct nfs4_state *state;
	unsigned long timeout = NFS4_LOCK_MINTIMEOUT;
	int status;

	/* verify open state */
	ctx = nfs_file_open_context(filp);
	state = ctx->state;

	if (request->fl_start < 0 || request->fl_end < 0)
		return -EINVAL;

	if (IS_GETLK(cmd)) {
		if (state != NULL)
			return nfs4_proc_getlk(state, F_GETLK, request);
		return 0;
	}

	if (!(IS_SETLK(cmd) || IS_SETLKW(cmd)))
		return -EINVAL;

	if (request->fl_type == F_UNLCK) {
		if (state != NULL)
			return nfs4_proc_unlck(state, cmd, request);
		return 0;
	}

	if (state == NULL)
		return -ENOLCK;
	/*
	 * Don't rely on the VFS having checked the file open mode,
	 * since it won't do this for flock() locks.
	 */
	switch (request->fl_type & (F_RDLCK|F_WRLCK|F_UNLCK)) {
	case F_RDLCK:
		if (!(filp->f_mode & FMODE_READ))
			return -EBADF;
		break;
	case F_WRLCK:
		if (!(filp->f_mode & FMODE_WRITE))
			return -EBADF;
	}

	do {
		status = nfs4_proc_setlk(state, cmd, request);
		if ((status != -EAGAIN) || IS_SETLK(cmd))
			break;
		timeout = nfs4_set_lock_task_retry(timeout);
		status = -ERESTARTSYS;
		if (signalled())
			break;
	} while(status < 0);
	return status;
}