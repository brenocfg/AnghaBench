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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_INFO_CALL_PIDFILEPORTINFO ; 
 int __proc_info (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int) ; 

int
proc_pidfileportinfo(int pid, uint32_t fileport, int flavor, void *buffer, int buffersize)
{
	int retval;

	if ((retval = __proc_info(PROC_INFO_CALL_PIDFILEPORTINFO, pid, flavor, (uint64_t)fileport, buffer, buffersize)) == -1)
		return (0);
	return (retval);
}