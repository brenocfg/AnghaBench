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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SYNC_HAS_STP ; 
 int /*<<< orphan*/  CLOCK_SYNC_STP ; 
 size_t EINVAL ; 
 size_t EOPNOTSUPP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_sync_flags ; 
 int /*<<< orphan*/  clock_sync_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stp_online ; 
 int /*<<< orphan*/  stp_work ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_sync_wq ; 

__attribute__((used)) static ssize_t stp_online_store(struct sysdev_class *class,
				const char *buf, size_t count)
{
	unsigned int value;

	value = simple_strtoul(buf, NULL, 0);
	if (value != 0 && value != 1)
		return -EINVAL;
	if (!test_bit(CLOCK_SYNC_HAS_STP, &clock_sync_flags))
		return -EOPNOTSUPP;
	mutex_lock(&clock_sync_mutex);
	stp_online = value;
	if (stp_online)
		set_bit(CLOCK_SYNC_STP, &clock_sync_flags);
	else
		clear_bit(CLOCK_SYNC_STP, &clock_sync_flags);
	queue_work(time_sync_wq, &stp_work);
	mutex_unlock(&clock_sync_mutex);
	return count;
}