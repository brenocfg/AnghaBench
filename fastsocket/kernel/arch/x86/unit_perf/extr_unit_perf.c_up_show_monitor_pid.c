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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_up_monitor_pid ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int up_show_monitor_pid(char *page, char **start, off_t offset,
	int count, int *eof, void *data)
{
	return snprintf(page, count, "%lu\n", g_up_monitor_pid);
}