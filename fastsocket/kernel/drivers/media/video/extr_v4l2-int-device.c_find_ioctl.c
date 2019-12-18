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
typedef  int /*<<< orphan*/  v4l2_int_ioctl_func ;
struct v4l2_int_slave {int num_ioctls; struct v4l2_int_ioctl_desc* ioctls; } ;
struct v4l2_int_ioctl_desc {int num; int /*<<< orphan*/ * func; } ;

/* Variables and functions */

__attribute__((used)) static v4l2_int_ioctl_func *find_ioctl(struct v4l2_int_slave *slave, int cmd,
				       v4l2_int_ioctl_func *no_such_ioctl)
{
	const struct v4l2_int_ioctl_desc *first = slave->ioctls;
	const struct v4l2_int_ioctl_desc *last =
		first + slave->num_ioctls - 1;

	while (first <= last) {
		const struct v4l2_int_ioctl_desc *mid;

		mid = (last - first) / 2 + first;

		if (mid->num < cmd)
			first = mid + 1;
		else if (mid->num > cmd)
			last = mid - 1;
		else
			return mid->func;
	}

	return no_such_ioctl;
}