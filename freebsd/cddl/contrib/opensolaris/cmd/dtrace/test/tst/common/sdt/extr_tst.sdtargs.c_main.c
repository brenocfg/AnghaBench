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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

int
main(int argc, char **argv)
{
	int val = 1;

	while (1) {
		if (sysctlbyname("debug.dtracetest.sdttest", NULL, NULL, &val,
		    sizeof(val)))
			err(1, "sysctlbyname");

		sleep(1);
	}

	return (0);
}