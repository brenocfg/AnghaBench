#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct necp_fd_data {int dummy; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {scalar_t__ fg_data; } ;

/* Variables and functions */
#define  FREAD 128 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 int POLLIN ; 
 int necp_fd_poll (struct necp_fd_data*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
necpop_select(struct fileproc *fp, int which, void *wql, vfs_context_t ctx)
{
#pragma unused(fp, which, wql, ctx)
	return (0);
	struct necp_fd_data *fd_data = NULL;
	int revents = 0;
	int events = 0;
	proc_t procp;

	fd_data = (struct necp_fd_data *)fp->f_fglob->fg_data;
	if (fd_data == NULL) {
		return (0);
	}

	procp = vfs_context_proc(ctx);

	switch (which) {
		case FREAD: {
			events = POLLIN;
			break;
		}

		default: {
			return (1);
		}
	}

	NECP_FD_LOCK(fd_data);
	revents = necp_fd_poll(fd_data, events, wql, procp, 0);
	NECP_FD_UNLOCK(fd_data);

	return ((events & revents) ? 1 : 0);
}