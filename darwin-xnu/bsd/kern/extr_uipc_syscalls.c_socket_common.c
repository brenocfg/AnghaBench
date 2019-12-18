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
struct socket {int dummy; } ;
struct proc {int dummy; } ;
struct fileproc {int f_flag; scalar_t__ f_data; int /*<<< orphan*/ * f_ops; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DBG_FUNC_START ; 
 int EACCES ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_NET_PRIVILEGED_SOCKET_DELEGATE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int falloc (struct proc*,struct fileproc**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  fp_free (struct proc*,int,struct fileproc*) ; 
 int /*<<< orphan*/  kEnTrActKernSocket ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int mac_socket_check_create (int /*<<< orphan*/ ,int,int,int) ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (struct proc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket ; 
 int /*<<< orphan*/  socketops ; 
 int socreate (int,struct socket**,int,int) ; 
 int socreate_delegate (int,struct socket**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 

__attribute__((used)) static int
socket_common(struct proc *p,
		int domain,
		int type,
		int protocol,
		pid_t epid,
		int32_t *retval,
		int delegate)
{
	struct socket *so;
	struct fileproc *fp;
	int fd, error;

	AUDIT_ARG(socket, domain, type, protocol);
#if CONFIG_MACF_SOCKET_SUBSET
	if ((error = mac_socket_check_create(kauth_cred_get(), domain,
	    type, protocol)) != 0)
		return (error);
#endif /* MAC_SOCKET_SUBSET */

	if (delegate) {
		error = priv_check_cred(kauth_cred_get(),
		    PRIV_NET_PRIVILEGED_SOCKET_DELEGATE, 0);
		if (error)
			return (EACCES);
	}

	error = falloc(p, &fp, &fd, vfs_context_current());
	if (error) {
		return (error);
	}
	fp->f_flag = FREAD|FWRITE;
	fp->f_ops = &socketops;

	if (delegate)
		error = socreate_delegate(domain, &so, type, protocol, epid);
	else
		error = socreate(domain, &so, type, protocol);

	if (error) {
		fp_free(p, fd, fp);
	} else {
		fp->f_data = (caddr_t)so;

		proc_fdlock(p);
		procfdtbl_releasefd(p, fd, NULL);

		fp_drop(p, fd, fp, 1);
		proc_fdunlock(p);

		*retval = fd;
		if (ENTR_SHOULDTRACE) {
			KERNEL_ENERGYTRACE(kEnTrActKernSocket, DBG_FUNC_START,
			    fd, 0, (int64_t)VM_KERNEL_ADDRPERM(so));
		}
	}
	return (error);
}