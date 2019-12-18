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
typedef  int __u32 ;

/* Variables and functions */
 int signal_processor_ps (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigp_sense ; 
#define  sigp_status_stored 128 

__attribute__((used)) static int cpu_stopped(int cpu)
{
	__u32 status;

	switch (signal_processor_ps(&status, 0, cpu, sigp_sense)) {
	case sigp_status_stored:
		/* Check for stopped and check stop state */
		if (status & 0x50)
			return 1;
		break;
	default:
		break;
	}
	return 0;
}