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
 int slow_work_may_not_start_new_thread ; 

__attribute__((used)) static void slow_work_oom_timeout(unsigned long data)
{
	slow_work_may_not_start_new_thread = false;
}