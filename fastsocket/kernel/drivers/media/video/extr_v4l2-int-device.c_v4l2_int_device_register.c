#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_int_ioctl_desc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* slave; } ;
struct v4l2_int_device {scalar_t__ type; int /*<<< orphan*/  head; TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_ioctls; int /*<<< orphan*/  ioctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  int_list ; 
 int /*<<< orphan*/  ioctl_sort_cmp ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_int_device_try_attach_all () ; 
 scalar_t__ v4l2_int_type_slave ; 

int v4l2_int_device_register(struct v4l2_int_device *d)
{
	if (d->type == v4l2_int_type_slave)
		sort(d->u.slave->ioctls, d->u.slave->num_ioctls,
		     sizeof(struct v4l2_int_ioctl_desc),
		     &ioctl_sort_cmp, NULL);
	mutex_lock(&mutex);
	list_add(&d->head, &int_list);
	v4l2_int_device_try_attach_all();
	mutex_unlock(&mutex);

	return 0;
}