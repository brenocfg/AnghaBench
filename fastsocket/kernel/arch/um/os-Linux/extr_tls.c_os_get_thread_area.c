#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  entry_number; } ;
typedef  TYPE_1__ user_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_GET_THREAD_AREA ; 
 int errno ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 

int os_get_thread_area(user_desc_t *info, int pid)
{
	int ret;

	ret = ptrace(PTRACE_GET_THREAD_AREA, pid, info->entry_number,
		     (unsigned long) info);
	if (ret < 0)
		ret = -errno;
	return ret;
}