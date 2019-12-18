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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSOCKET_ERR (char*) ; 
 int /*<<< orphan*/  INIT_FDSET_NUM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fsocket_channel_fd ; 
 int /*<<< orphan*/  fsocket_fd_num ; 
 int /*<<< orphan*/  fsocket_fd_set ; 
 int get_cpus () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((constructor))
void fastsocket_init(void)
{
	int ret = 0;
	int i;
	cpu_set_t cmask;

	ret = open("/dev/fastsocket", O_RDONLY);
	if (ret < 0) {
		FSOCKET_ERR("Open fastsocket channel failed, please CHECK\n");
		/* Just exit for safty*/
		exit(-1);
	}
	fsocket_channel_fd = ret;

	fsocket_fd_set = calloc(INIT_FDSET_NUM, sizeof(int));
	if (!fsocket_fd_set) {
		FSOCKET_ERR("Allocate memory for listen fd set failed\n");
		exit(-1);
	}

	fsocket_fd_num = INIT_FDSET_NUM;

	CPU_ZERO(&cmask);

	for (i = 0; i < get_cpus(); i++)
		CPU_SET(i, &cmask);

	ret = sched_setaffinity(0, get_cpus(), &cmask);
	if (ret < 0) {
		FSOCKET_ERR("Clear process CPU affinity failed\n");
		exit(-1);
	}

	return;
}