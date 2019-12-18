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
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int PRIO_DARWIN_THREAD ; 
 int __setpriority (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _pthread_clear_qos_tsd (int /*<<< orphan*/ ) ; 

int
setpriority(int which, id_t who, int prio)
{
	int rv = __setpriority(which, who, prio);
	if (which == PRIO_DARWIN_THREAD && rv == -2) {
		_pthread_clear_qos_tsd(MACH_PORT_NULL);
		rv = 0;
	}

	return rv;
}