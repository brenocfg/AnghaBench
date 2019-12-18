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
struct fsocket_ioctl_arg {int /*<<< orphan*/  fd; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR ; 
 int FMODE_FASTSOCKET ; 
 int /*<<< orphan*/  INFO ; 
 struct file* fget_light (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int fsocket_close (int /*<<< orphan*/ ) ; 
 int sys_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fastsocket_close(struct fsocket_ioctl_arg * arg)
{
	int error;
	struct file *tfile;
	int fput_need;

	DPRINTK(DEBUG,"Close fastsocket %d\n", arg->fd);

	tfile = fget_light(arg->fd, &fput_need);
	if (tfile == NULL) {
		EPRINTK_LIMIT(ERR, "Close file don't exist!\n");
		return -EINVAL;
	}

	if (tfile->f_mode & FMODE_FASTSOCKET) {
		fput_light(tfile, fput_need);
		error = fsocket_close(arg->fd);
	} else {
		fput_light(tfile, fput_need);
		DPRINTK(INFO, "Close non fastsocket %d\n", arg->fd);
		error = sys_close(arg->fd);
	}

	return error;
}