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
struct mbcs_soft {int /*<<< orphan*/  algo_done; int /*<<< orphan*/  algo_queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cx_dev {struct mbcs_soft* soft; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ERESTARTSYS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbcs_algo_start (struct mbcs_soft*) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cx_dev* to_cx_dev (struct device*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_algo(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int n;
	struct cx_dev *cx_dev = to_cx_dev(dev);
	struct mbcs_soft *soft = cx_dev->soft;

	if (count <= 0)
		return 0;

	n = simple_strtoul(buf, NULL, 0);

	if (n == 1) {
		mbcs_algo_start(soft);
		if (wait_event_interruptible(soft->algo_queue,
					atomic_read(&soft->algo_done)))
			return -ERESTARTSYS;
	}

	return count;
}