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
typedef  int /*<<< orphan*/  u_long ;
struct socket {int dummy; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int EBADF ; 
 int soioctl (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

int
soo_ioctl(struct fileproc *fp, u_long cmd, caddr_t data, vfs_context_t ctx)
{
	struct socket *so;
	proc_t procp = vfs_context_proc(ctx);

	if ((so = (struct socket *)fp->f_fglob->fg_data) == NULL) {
		/* This is not a valid open file descriptor */
		return (EBADF);
	}

	return (soioctl(so, cmd, data, procp));
}