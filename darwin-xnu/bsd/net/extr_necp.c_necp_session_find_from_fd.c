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
struct necp_session {scalar_t__ necp_fd_type; } ;
struct fileproc {TYPE_2__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_4__ {scalar_t__ fg_data; TYPE_1__* fg_ops; } ;
struct TYPE_3__ {scalar_t__ fo_type; } ;

/* Variables and functions */
 scalar_t__ DTYPE_NETPOLICY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int) ; 
 scalar_t__ necp_fd_type_session ; 
 int /*<<< orphan*/  proc_fdlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
necp_session_find_from_fd(int fd, struct necp_session **session)
{
	proc_t p = current_proc();
	struct fileproc *fp = NULL;
	int error = 0;

	proc_fdlock_spin(p);
	if ((error = fp_lookup(p, fd, &fp, 1)) != 0) {
		goto done;
	}
	if (fp->f_fglob->fg_ops->fo_type != DTYPE_NETPOLICY) {
		fp_drop(p, fd, fp, 1);
		error = ENODEV;
		goto done;
	}
	*session = (struct necp_session *)fp->f_fglob->fg_data;

	if ((*session)->necp_fd_type != necp_fd_type_session) {
		// Not a client fd, ignore
		error = EINVAL;
		goto done;
	}

done:
	proc_fdunlock(p);
	return (error);
}