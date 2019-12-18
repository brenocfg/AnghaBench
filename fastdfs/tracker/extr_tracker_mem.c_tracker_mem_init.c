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
 int /*<<< orphan*/  g_groups ; 
 int init_pthread_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_file_lock ; 
 int /*<<< orphan*/  mem_thread_lock ; 
 int tracker_mem_init_groups (int /*<<< orphan*/ *) ; 
 int tracker_open_changlog_file () ; 

int tracker_mem_init()
{
	int result;

	if ((result=init_pthread_lock(&mem_thread_lock)) != 0)
	{
		return result;
	}

	if ((result=init_pthread_lock(&mem_file_lock)) != 0)
	{
		return result;
	}

	if ((result=tracker_open_changlog_file()) != 0)
	{
		return result;
	}

	return tracker_mem_init_groups(&g_groups);
}