#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vi ;
struct TYPE_7__ {int /*<<< orphan*/  vi_stat; } ;
struct TYPE_6__ {int fi_openflags; } ;
struct vnode_fdinfo {TYPE_2__ pvi; TYPE_1__ pfi; } ;
struct proc_fdinfo {int proc_fdtype; int /*<<< orphan*/  proc_fd; } ;
typedef  TYPE_3__* fdOpenInfoRef ;
struct TYPE_8__ {int fds_size; int fds_count; int flags; struct proc_fdinfo* fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int O_EVTONLY ; 
 int PROC_LISTPIDSPATH_EXCLUDE_EVTONLY ; 
 int /*<<< orphan*/  PROC_PIDFDVNODEINFO ; 
 int /*<<< orphan*/  PROC_PIDLISTFDS ; 
#define  PROX_FDTYPE_VNODE 128 
 int check_file (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 struct proc_fdinfo* malloc (int) ; 
 int proc_pidfdinfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode_fdinfo*,int) ; 
 int proc_pidinfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_fdinfo*,int) ; 
 struct proc_fdinfo* reallocf (struct proc_fdinfo*,int) ; 

__attribute__((used)) static int
check_process_fds(fdOpenInfoRef info, int pid)
{
	int	buf_used;
	int	i;
	int	status;

	// get list of open file descriptors
	buf_used = proc_pidinfo(pid, PROC_PIDLISTFDS, 0, NULL, 0);
	if (buf_used <= 0) {
		return -1;
	}

	while (1) {
		if (buf_used > info->fds_size) {
			// if we need to allocate [more] space
			while (buf_used > info->fds_size) {
				info->fds_size += (sizeof(struct proc_fdinfo) * 32);
			}

			if (info->fds == NULL) {
				info->fds = malloc(info->fds_size);
			} else {
				info->fds = reallocf(info->fds, info->fds_size);
			}
			if (info->fds == NULL) {
				return -1;
			}
		}

		buf_used = proc_pidinfo(pid, PROC_PIDLISTFDS, 0, info->fds, (int)info->fds_size);
		if (buf_used <= 0) {
			return -1;
		}

		if ((buf_used + sizeof(struct proc_fdinfo)) >= info->fds_size) {
			// if not enough room in the buffer for an extra fd
			buf_used = (int)(info->fds_size + sizeof(struct proc_fdinfo));
			continue;
		}

		info->fds_count = (int)(buf_used / sizeof(struct proc_fdinfo));
		break;
	}

	// iterate through each file descriptor
	for (i = 0; i < info->fds_count; i++) {
		struct proc_fdinfo	*fdp;

		fdp = &info->fds[i];
		switch (fdp->proc_fdtype) {
			case PROX_FDTYPE_VNODE : {
				int			buf_used;
				struct vnode_fdinfo	vi;

				buf_used = proc_pidfdinfo(pid, fdp->proc_fd, PROC_PIDFDVNODEINFO, &vi, sizeof(vi));
				if (buf_used <= 0) {
					if (errno == ENOENT) {
						/*
						 * The file descriptor's vnode may have been revoked. This is a
						 * bit of a hack, since an ENOENT error might not always mean the
						 * descriptor's vnode has been revoked. As the libproc API
						 * matures, this code may need to be revisited.
						 */
						continue;
					}
					return -1;
				} else if (buf_used < sizeof(vi)) {
					// if we didn't get enough information
					return -1;
				}

				if ((info->flags & PROC_LISTPIDSPATH_EXCLUDE_EVTONLY) &&
				    (vi.pfi.fi_openflags & O_EVTONLY)) {
					// if this file should be excluded
					continue;
				}

				status = check_file(info, &vi.pvi.vi_stat);
				if (status != 0) {
					// if error or match
					return status;
				}
				break;
			}
			default :
				break;
		}
	}

	return 0;
}