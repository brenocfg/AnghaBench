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
struct cpumask {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int cpulist_scnprintf (char*,scalar_t__,struct cpumask const*) ; 

__attribute__((used)) static ssize_t print_cpus_map(char *buf, const struct cpumask *map)
{
	int n = cpulist_scnprintf(buf, PAGE_SIZE-2, map);

	buf[n++] = '\n';
	buf[n] = '\0';
	return n;
}