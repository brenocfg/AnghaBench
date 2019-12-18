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
struct fsocket_ioctl_arg {int fd; int backlog; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR ; 
 int FMODE_BIND_EPI ; 
 int FMODE_FASTSOCKET ; 
 int FMODE_SINGLE_WAKEUP ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ enable_fast_epoll ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int fsocket_listen (struct file*,int) ; 
 int sys_listen (int,int) ; 

__attribute__((used)) static int fastsocket_listen(struct fsocket_ioctl_arg *arg)
{
	struct file *tfile;
	int fd, backlog, ret, fput_needed;

	fd = arg->fd;
	backlog = arg->backlog;

	tfile = fget_light(fd, &fput_needed);
	if (tfile == NULL) {
		EPRINTK_LIMIT(ERR, "fd [%d] file doesn't exist!\n", fd);
		return -EINVAL;
	}

	if (tfile->f_mode & FMODE_FASTSOCKET) {
		DPRINTK(DEBUG,"Listen fastsocket %d\n", fd);
		if (enable_fast_epoll) {
			/* For listen fastsocket, set single-wakeup and reset bind-epi */
			tfile->f_mode |= FMODE_SINGLE_WAKEUP;
			tfile->f_mode &= ~FMODE_BIND_EPI;
		}
		ret = fsocket_listen(tfile, backlog);
	} else {
		DPRINTK(INFO, "Listen non-fastsocket %d\n", fd);
		ret = sys_listen(fd, backlog);
	}

	fput_light(tfile, fput_needed);

	return ret;
}