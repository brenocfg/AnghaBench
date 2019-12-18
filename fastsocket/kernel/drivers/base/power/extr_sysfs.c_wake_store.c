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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  device_can_wakeup (struct device*) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (struct device*,int) ; 
 int /*<<< orphan*/  disabled ; 
 int /*<<< orphan*/  enabled ; 
 char* memchr (char const*,char,size_t) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
wake_store(struct device * dev, struct device_attribute *attr,
	const char * buf, size_t n)
{
	char *cp;
	int len = n;

	if (!device_can_wakeup(dev))
		return -EINVAL;

	cp = memchr(buf, '\n', n);
	if (cp)
		len = cp - buf;
	if (len == sizeof enabled - 1
			&& strncmp(buf, enabled, sizeof enabled - 1) == 0)
		device_set_wakeup_enable(dev, 1);
	else if (len == sizeof disabled - 1
			&& strncmp(buf, disabled, sizeof disabled - 1) == 0)
		device_set_wakeup_enable(dev, 0);
	else
		return -EINVAL;
	return n;
}