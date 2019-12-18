#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* slave; } ;
struct v4l2_int_device {scalar_t__ type; TYPE_4__ u; int /*<<< orphan*/  head; } ;
struct TYPE_7__ {TYPE_1__* master; } ;
struct TYPE_10__ {int /*<<< orphan*/  module; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_5__* master; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* detach ) (struct v4l2_int_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_int_device*) ; 
 scalar_t__ v4l2_int_type_slave ; 

void v4l2_int_device_unregister(struct v4l2_int_device *d)
{
	mutex_lock(&mutex);
	list_del(&d->head);
	if (d->type == v4l2_int_type_slave
	    && d->u.slave->master != NULL) {
		d->u.slave->master->u.master->detach(d);
		module_put(d->u.slave->master->module);
		d->u.slave->master = NULL;
	}
	mutex_unlock(&mutex);
}