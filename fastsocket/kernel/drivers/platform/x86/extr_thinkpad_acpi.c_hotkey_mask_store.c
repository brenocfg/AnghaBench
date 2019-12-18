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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  hotkey_mutex ; 
 int /*<<< orphan*/  hotkey_poll_setup (int) ; 
 int hotkey_user_mask_set (unsigned long) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_strtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  tpacpi_disclose_usertask (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t hotkey_mask_store(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	unsigned long t;
	int res;

	if (parse_strtoul(buf, 0xffffffffUL, &t))
		return -EINVAL;

	if (mutex_lock_killable(&hotkey_mutex))
		return -ERESTARTSYS;

	res = hotkey_user_mask_set(t);

#ifdef CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	hotkey_poll_setup(true);
#endif

	mutex_unlock(&hotkey_mutex);

	tpacpi_disclose_usertask("hotkey_mask", "set to 0x%08lx\n", t);

	return (res) ? res : count;
}