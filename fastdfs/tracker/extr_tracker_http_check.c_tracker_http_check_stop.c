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
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ g_http_check_interval ; 
 int /*<<< orphan*/  http_check_tid ; 
 int pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tracker_http_check_stop()
{
	if (g_http_check_interval <= 0)
	{
		return 0;
	}

	return pthread_kill(http_check_tid, SIGINT);
}