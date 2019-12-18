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
typedef  scalar_t__ kqueue_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_INFO_CALL_PIDDYNKQUEUEINFO ; 
 int __proc_info (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int) ; 

int
proc_piddynkqueueinfo(int pid, int flavor, kqueue_id_t kq_id, void *buffer, int buffersize)
{
	int ret;

	if ((ret = __proc_info(PROC_INFO_CALL_PIDDYNKQUEUEINFO, pid, flavor, (uint64_t)kq_id, buffer, buffersize)) == -1) {
		return 0;
	}

	return ret;
}