#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sysdev_attribute {int dummy; } ;
struct sys_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int e0; int e1; } ;

/* Variables and functions */
 TYPE_1__ etr_eacr ; 
 struct sys_device etr_port0_dev ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t etr_stepping_control_show(struct sys_device *dev,
					struct sysdev_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%i\n", (dev == &etr_port0_dev) ?
		       etr_eacr.e0 : etr_eacr.e1);
}