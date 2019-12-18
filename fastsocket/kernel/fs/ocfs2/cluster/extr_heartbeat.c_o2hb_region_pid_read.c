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
struct o2hb_region {scalar_t__ hr_task; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int task_pid_nr (scalar_t__) ; 

__attribute__((used)) static ssize_t o2hb_region_pid_read(struct o2hb_region *reg,
                                      char *page)
{
	pid_t pid = 0;

	spin_lock(&o2hb_live_lock);
	if (reg->hr_task)
		pid = task_pid_nr(reg->hr_task);
	spin_unlock(&o2hb_live_lock);

	if (!pid)
		return 0;

	return sprintf(page, "%u\n", pid);
}