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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ bootstrap_look_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int num_servers ; 
 int /*<<< orphan*/ * server_port_name ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ task_get_bootstrap_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
wait_for_servers(void)
{
	int		i;
	int		retry_count = 10;
	mach_port_t	bsport, servport;
	kern_return_t	ret;

	/* find server port */
	ret = task_get_bootstrap_port(mach_task_self(), &bsport);
	if (KERN_SUCCESS != ret) {
		mach_error("task_get_bootstrap_port(): ", ret);
		exit(1);
	}

	while (retry_count-- > 0) {
		for (i = 0; i < num_servers; i++) {
			ret = bootstrap_look_up(bsport,
					server_port_name[i],
					&servport); 
			if (ret != KERN_SUCCESS) {
				break;
			}
		}
		if (ret == KERN_SUCCESS)
			return;
		usleep(100 * 1000);	/* 100ms */
	}
	fprintf(stderr, "Server(s) failed to register\n");
	exit(1);
}