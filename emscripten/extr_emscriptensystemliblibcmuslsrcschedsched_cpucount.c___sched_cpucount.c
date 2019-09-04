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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */

int __sched_cpucount(size_t size, const cpu_set_t *set)
{
	size_t i, j, cnt=0;
	const unsigned char *p = (const void *)set;
	for (i=0; i<size; i++) for (j=0; j<8; j++)
		if (p[i] & (1<<j)) cnt++;
	return cnt;
}