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
struct TYPE_3__ {int cpu; } ;
struct TYPE_4__ {TYPE_1__ spawn_op; } ;
struct fsocket_ioctl_arg {int fd; TYPE_2__ op; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR ; 
 int FMODE_FASTSOCKET ; 
 int /*<<< orphan*/  INFO ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int fsocket_spawn (struct file*,int,int) ; 

__attribute__((used)) static int fastsocket_spawn_listen(struct fsocket_ioctl_arg *arg)
{
	struct file *tfile;
	int fd, tcpu, ret, fput_needed;

	DPRINTK(DEBUG, "Listen spawn listen fd %d\n", arg->fd);

	fd = arg->fd;
	tcpu = arg->op.spawn_op.cpu;

	tfile = fget_light(fd, &fput_needed);
	if (tfile == NULL) {
		EPRINTK_LIMIT(ERR, "fd [%d] doesn't exist!\n", fd);
		return -EINVAL;
	}

	if (tfile->f_mode & FMODE_FASTSOCKET)
		ret = fsocket_spawn(tfile, fd, tcpu);
	else {
		DPRINTK(INFO, "Spawn non fastsocket\n");
		return -EINVAL;
	}

	fput_light(tfile, fput_needed);

	return ret;
}