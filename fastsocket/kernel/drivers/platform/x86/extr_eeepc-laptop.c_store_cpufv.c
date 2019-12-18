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
struct eeepc_cpufv {int num; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ cpufv_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_CPUFV ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 TYPE_1__* ehotk ; 
 scalar_t__ get_cpufv (struct eeepc_cpufv*) ; 
 int parse_arg (char const*,size_t,int*) ; 
 int /*<<< orphan*/  set_acpi (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t store_cpufv(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct eeepc_cpufv c;
	int rv, value;

	if (ehotk->cpufv_disabled)
		return -EPERM;
	if (get_cpufv(&c))
		return -ENODEV;
	rv = parse_arg(buf, count, &value);
	if (rv < 0)
		return rv;
	if (!rv || value < 0 || value >= c.num)
		return -EINVAL;
	set_acpi(CM_ASL_CPUFV, value);
	return rv;
}