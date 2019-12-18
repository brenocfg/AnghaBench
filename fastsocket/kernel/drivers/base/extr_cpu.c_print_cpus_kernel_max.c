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
struct sysdev_class {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int NR_CPUS ; 
 scalar_t__ PAGE_SIZE ; 
 int snprintf (char*,scalar_t__,char*,int) ; 

__attribute__((used)) static ssize_t print_cpus_kernel_max(struct sysdev_class *class, char *buf)
{
	int n = snprintf(buf, PAGE_SIZE-2, "%d\n", NR_CPUS - 1);
	return n;
}