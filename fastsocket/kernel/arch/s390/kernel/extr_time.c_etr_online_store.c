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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SYNC_ETR ; 
 int /*<<< orphan*/  CLOCK_SYNC_HAS_ETR ; 
 size_t EINVAL ; 
 size_t EOPNOTSUPP ; 
 int /*<<< orphan*/  ETR_EVENT_PORT0_CHANGE ; 
 int /*<<< orphan*/  ETR_EVENT_PORT1_CHANGE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_sync_flags ; 
 int /*<<< orphan*/  clock_sync_mutex ; 
 int /*<<< orphan*/  etr_events ; 
 struct sys_device etr_port0_dev ; 
 unsigned int etr_port0_online ; 
 unsigned int etr_port1_online ; 
 int /*<<< orphan*/  etr_work ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_sync_wq ; 

__attribute__((used)) static ssize_t etr_online_store(struct sys_device *dev,
				struct sysdev_attribute *attr,
				const char *buf, size_t count)
{
	unsigned int value;

	value = simple_strtoul(buf, NULL, 0);
	if (value != 0 && value != 1)
		return -EINVAL;
	if (!test_bit(CLOCK_SYNC_HAS_ETR, &clock_sync_flags))
		return -EOPNOTSUPP;
	mutex_lock(&clock_sync_mutex);
	if (dev == &etr_port0_dev) {
		if (etr_port0_online == value)
			goto out;	/* Nothing to do. */
		etr_port0_online = value;
		if (etr_port0_online && etr_port1_online)
			set_bit(CLOCK_SYNC_ETR, &clock_sync_flags);
		else
			clear_bit(CLOCK_SYNC_ETR, &clock_sync_flags);
		set_bit(ETR_EVENT_PORT0_CHANGE, &etr_events);
		queue_work(time_sync_wq, &etr_work);
	} else {
		if (etr_port1_online == value)
			goto out;	/* Nothing to do. */
		etr_port1_online = value;
		if (etr_port0_online && etr_port1_online)
			set_bit(CLOCK_SYNC_ETR, &clock_sync_flags);
		else
			clear_bit(CLOCK_SYNC_ETR, &clock_sync_flags);
		set_bit(ETR_EVENT_PORT1_CHANGE, &etr_events);
		queue_work(time_sync_wq, &etr_work);
	}
out:
	mutex_unlock(&clock_sync_mutex);
	return count;
}