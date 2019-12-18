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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int attr_rdpmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  change_rdpmc ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,void*,int) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static ssize_t set_attr_rdpmc(struct device *cdev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	unsigned long val = simple_strtoul(buf, NULL, 0);

	if (!!val != !!x86_pmu.attr_rdpmc) {
		x86_pmu.attr_rdpmc = !!val;
		smp_call_function(change_rdpmc, (void *)val, 1);
	}

	return count;
}