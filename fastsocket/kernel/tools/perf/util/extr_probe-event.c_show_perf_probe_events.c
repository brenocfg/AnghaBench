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

/* Variables and functions */
 int __show_perf_probe_events (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int init_vmlinux () ; 
 int open_kprobe_events (int) ; 
 int open_uprobe_events (int) ; 
 int /*<<< orphan*/  setup_pager () ; 

int show_perf_probe_events(void)
{
	int fd, ret;

	setup_pager();
	fd = open_kprobe_events(false);

	if (fd < 0)
		return fd;

	ret = init_vmlinux();
	if (ret < 0)
		return ret;

	ret = __show_perf_probe_events(fd, true);
	close(fd);

	fd = open_uprobe_events(false);
	if (fd >= 0) {
		ret = __show_perf_probe_events(fd, false);
		close(fd);
	}

	return ret;
}