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
struct TYPE_3__ {int /*<<< orphan*/  how; } ;
struct TYPE_4__ {TYPE_1__ shutdown_op; } ;
struct fsocket_ioctl_arg {TYPE_2__ op; int /*<<< orphan*/  fd; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR ; 
 int FMODE_FASTSOCKET ; 
 int /*<<< orphan*/  INFO ; 
 struct file* fget_light (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int fsocket_shutdown_listen (struct file*,int /*<<< orphan*/ ) ; 
 int sys_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fastsocket_shutdown_listen(struct fsocket_ioctl_arg *arg)
{
	int ret;
	struct file *tfile;
	int fput_need;

	tfile =	fget_light(arg->fd, &fput_need);
	if (tfile == NULL) {
		EPRINTK_LIMIT(ERR, "Accept file don't exist!\n");
		return -ENOENT;
	}

	if (tfile->f_mode & FMODE_FASTSOCKET) {
		DPRINTK(DEBUG, "Shutdown fastsocket %d\n", arg->fd);
		ret = fsocket_shutdown_listen(tfile, arg->op.shutdown_op.how);
	} else {
		DPRINTK(INFO, "Shutdown non-fastsocket %d\n", arg->fd);
		ret = sys_shutdown(arg->fd, arg->op.shutdown_op.how);
	}
	fput_light(tfile, fput_need);

	return ret;
}