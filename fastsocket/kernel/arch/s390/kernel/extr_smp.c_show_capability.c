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
struct sysdev_attribute {int dummy; } ;
struct sys_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int get_cpu_capability (unsigned int*) ; 
 int sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t show_capability(struct sys_device *dev,
				struct sysdev_attribute *attr, char *buf)
{
	unsigned int capability;
	int rc;

	rc = get_cpu_capability(&capability);
	if (rc)
		return rc;
	return sprintf(buf, "%u\n", capability);
}