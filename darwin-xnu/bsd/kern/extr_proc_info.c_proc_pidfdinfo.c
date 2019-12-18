#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint32_t ;
struct pshmnode {int dummy; } ;
struct psemnode {int dummy; } ;
struct pipe {int dummy; } ;
struct kqueue {int dummy; } ;
struct fileproc {int dummy; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_23__ {TYPE_1__* p_fd; } ;
struct TYPE_22__ {struct kqueue* fd_wqkqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SAME_USER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ESRCH ; 
 int /*<<< orphan*/  PROC_INFO_CALL_PIDFDINFO ; 
 TYPE_2__* PROC_NULL ; 
#define  PROC_PIDFDATALKINFO 136 
 scalar_t__ PROC_PIDFDATALKINFO_SIZE ; 
#define  PROC_PIDFDKQUEUEINFO 135 
 scalar_t__ PROC_PIDFDKQUEUEINFO_SIZE ; 
#define  PROC_PIDFDKQUEUE_EXTINFO 134 
 scalar_t__ PROC_PIDFDKQUEUE_EXTINFO_SIZE ; 
#define  PROC_PIDFDPIPEINFO 133 
 scalar_t__ PROC_PIDFDPIPEINFO_SIZE ; 
#define  PROC_PIDFDPSEMINFO 132 
 scalar_t__ PROC_PIDFDPSEMINFO_SIZE ; 
#define  PROC_PIDFDPSHMINFO 131 
 scalar_t__ PROC_PIDFDPSHMINFO_SIZE ; 
#define  PROC_PIDFDSOCKETINFO 130 
 scalar_t__ PROC_PIDFDSOCKETINFO_SIZE ; 
#define  PROC_PIDFDVNODEINFO 129 
 scalar_t__ PROC_PIDFDVNODEINFO_SIZE ; 
#define  PROC_PIDFDVNODEPATHINFO 128 
 scalar_t__ PROC_PIDFDVNODEPATHINFO_SIZE ; 
 int /*<<< orphan*/  fp_drop (TYPE_2__*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_getfkq (TYPE_2__*,int,struct fileproc**,struct kqueue**) ; 
 int fp_getfpipe (TYPE_2__*,int,struct fileproc**,struct pipe**) ; 
 int fp_getfpsem (TYPE_2__*,int,struct fileproc**,struct psemnode**) ; 
 int fp_getfpshm (TYPE_2__*,int,struct fileproc**,struct pshmnode**) ; 
 int fp_getfsock (TYPE_2__*,int,struct fileproc**,int /*<<< orphan*/ *) ; 
 int fp_getfvpandvid (TYPE_2__*,int,struct fileproc**,int /*<<< orphan*/ *,scalar_t__*) ; 
 int pid_kqueue_extinfo (TYPE_2__*,struct kqueue*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_kqueueinfo (struct kqueue*,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_pipeinfo (struct pipe*,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_pseminfo (struct psemnode*,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_pshminfo (struct pshmnode*,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_socketinfo (int /*<<< orphan*/ ,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_vnodeinfo (int /*<<< orphan*/ ,scalar_t__,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int pid_vnodeinfopath (int /*<<< orphan*/ ,scalar_t__,struct fileproc*,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_2__*) ; 
 int proc_security_policy (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
proc_pidfdinfo(int pid, int flavor,  int fd, user_addr_t buffer, uint32_t buffersize, int32_t * retval)
{
	proc_t p;
	int error = ENOTSUP;
	struct fileproc * fp = NULL;
	uint32_t size;

	switch (flavor) {
		case PROC_PIDFDVNODEINFO:
			size = PROC_PIDFDVNODEINFO_SIZE;
			break;
		case PROC_PIDFDVNODEPATHINFO:
			size = PROC_PIDFDVNODEPATHINFO_SIZE;
			break;
		case PROC_PIDFDSOCKETINFO:
			size = PROC_PIDFDSOCKETINFO_SIZE;
			break;
		case PROC_PIDFDPSEMINFO:
			size = PROC_PIDFDPSEMINFO_SIZE;
			break;
		case PROC_PIDFDPSHMINFO:
			size = PROC_PIDFDPSHMINFO_SIZE;
			break;
		case PROC_PIDFDPIPEINFO:
			size = PROC_PIDFDPIPEINFO_SIZE;
			break;
		case PROC_PIDFDKQUEUEINFO:
			size = PROC_PIDFDKQUEUEINFO_SIZE;
			break;
		case PROC_PIDFDKQUEUE_EXTINFO:
			size = PROC_PIDFDKQUEUE_EXTINFO_SIZE;
			if (buffer == (user_addr_t)0)
				size = 0;
			break;
		case PROC_PIDFDATALKINFO:
			size = PROC_PIDFDATALKINFO_SIZE;
			break;

		default:
			return(EINVAL);

	}

	if (buffersize < size)
		return(ENOMEM);

	if ((p = proc_find(pid)) == PROC_NULL) {
		error = ESRCH;
		goto out;
	}

	/* Do we have permission to look into this? */
	if ((error = proc_security_policy(p, PROC_INFO_CALL_PIDFDINFO, flavor, CHECK_SAME_USER)))
		goto out1;

	switch (flavor) {
		case PROC_PIDFDVNODEINFO: {
			vnode_t vp;
			uint32_t vid=0;

			if ((error = fp_getfvpandvid(p, fd, &fp,  &vp, &vid)) !=0) {
				goto out1;
			}
			/* no need to be under the fdlock */
			error =  pid_vnodeinfo(vp, vid, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDVNODEPATHINFO: {
			vnode_t vp;
			uint32_t vid=0;

			if ((error = fp_getfvpandvid(p, fd, &fp,  &vp, &vid)) !=0) {
				goto out1;
			}

			/* no need to be under the fdlock */
			error =  pid_vnodeinfopath(vp, vid, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDSOCKETINFO: {
			socket_t so; 

			if ((error = fp_getfsock(p, fd, &fp,  &so)) !=0) {
				goto out1;
			}
			/* no need to be under the fdlock */
			error =  pid_socketinfo(so, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDPSEMINFO: {
			struct psemnode * psem;

			if ((error = fp_getfpsem(p, fd, &fp,  &psem)) !=0) {
				goto out1;
			}
			/* no need to be under the fdlock */
			error =  pid_pseminfo(psem, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDPSHMINFO: {
			struct pshmnode * pshm;

			if ((error = fp_getfpshm(p, fd, &fp,  &pshm)) !=0) {
				goto out1;
			}
			/* no need to be under the fdlock */
			error =  pid_pshminfo(pshm, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDPIPEINFO: {
			struct pipe * cpipe;

			if ((error = fp_getfpipe(p, fd, &fp,  &cpipe)) !=0) {
				goto out1;
			}
			/* no need to be under the fdlock */
			error =  pid_pipeinfo(cpipe, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDKQUEUEINFO: {
			struct kqueue * kq;

			if (fd == -1) {
				if ((kq = p->p_fd->fd_wqkqueue) == NULL) {
					/* wqkqueue is initialized on-demand */
					error = 0;
					break;
				}
			} else if ((error = fp_getfkq(p, fd, &fp,  &kq)) != 0) {
				goto out1;
			}

			/* no need to be under the fdlock */
			error = pid_kqueueinfo(kq, fp, p, fd, buffer, buffersize, retval);
		}
		break;

		case PROC_PIDFDKQUEUE_EXTINFO: {
			struct kqueue * kq;

			if (fd == -1) {
				if ((kq = p->p_fd->fd_wqkqueue) == NULL) {
					/* wqkqueue is initialized on-demand */
					error = 0;
					break;
				}
			} else if ((error = fp_getfkq(p, fd, &fp, &kq)) != 0) {
				goto out1;
			}
			error = pid_kqueue_extinfo(p, kq, buffer, buffersize, retval);
		}
		break;

		default: {
			error = EINVAL;
			goto out1;
		}
	}

	if (fp) {
		fp_drop(p, fd, fp , 0);
	}
out1 :
	proc_rele(p);
out:
	return(error);
}