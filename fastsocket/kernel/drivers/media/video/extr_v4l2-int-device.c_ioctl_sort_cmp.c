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
struct v4l2_int_ioctl_desc {scalar_t__ num; } ;

/* Variables and functions */

__attribute__((used)) static int ioctl_sort_cmp(const void *a, const void *b)
{
	const struct v4l2_int_ioctl_desc *d1 = a, *d2 = b;

	if (d1->num > d2->num)
		return 1;

	if (d1->num < d2->num)
		return -1;

	return 0;
}