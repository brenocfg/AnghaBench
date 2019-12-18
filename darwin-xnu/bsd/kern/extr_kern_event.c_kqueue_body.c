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
struct proc {int dummy; } ;
struct kqueue {int dummy; } ;
struct fileproc {int f_flag; struct kqueue* f_data; int /*<<< orphan*/ * f_ops; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  fp_allocfn_t ;

/* Variables and functions */
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  UF_EXCLOSE ; 
 int falloc_withalloc (struct proc*,struct fileproc**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * fdflags (struct proc*,int) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  fp_free (struct proc*,int,struct fileproc*) ; 
 struct kqueue* kqueue_alloc (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqueueops ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (struct proc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_current () ; 

int
kqueue_body(struct proc *p, fp_allocfn_t fp_zalloc, void *cra, int32_t *retval)
{
	struct kqueue *kq;
	struct fileproc *fp;
	int fd, error;

	error = falloc_withalloc(p,
	    &fp, &fd, vfs_context_current(), fp_zalloc, cra);
	if (error) {
		return (error);
	}

	kq = kqueue_alloc(p, 0);
	if (kq == NULL) {
		fp_free(p, fd, fp);
		return (ENOMEM);
	}

	fp->f_flag = FREAD | FWRITE;
	fp->f_ops = &kqueueops;
	fp->f_data = kq;

	proc_fdlock(p);
	*fdflags(p, fd) |= UF_EXCLOSE;
	procfdtbl_releasefd(p, fd, NULL);
	fp_drop(p, fd, fp, 1);
	proc_fdunlock(p);

	*retval = fd;
	return (error);
}