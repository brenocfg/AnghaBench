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
struct sysctl_req {int dummy; } ;
typedef  int /*<<< orphan*/  should_reset ;

/* Variables and functions */
 int /*<<< orphan*/  KTRACE_KPERF ; 
 int /*<<< orphan*/  ktrace_reset (int /*<<< orphan*/ ) ; 
 int sysctl_io_number (struct sysctl_req*,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sysctl_kperf_reset(struct sysctl_req *req)
{
	int should_reset = 0;

	int error = sysctl_io_number(req, should_reset, sizeof(should_reset),
		&should_reset, NULL);
	if (error) {
		return error;
	}

	if (should_reset) {
		ktrace_reset(KTRACE_KPERF);
	}
	return 0;
}