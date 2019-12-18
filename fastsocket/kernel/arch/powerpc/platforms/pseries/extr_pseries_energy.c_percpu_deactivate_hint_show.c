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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_best_energy_data (struct sys_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t percpu_deactivate_hint_show(struct sys_device *dev,
			struct sysdev_attribute *attr, char *page)
{
	return get_best_energy_data(dev, page, 0);
}