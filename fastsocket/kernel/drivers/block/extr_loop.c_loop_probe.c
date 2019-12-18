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
struct loop_device {int /*<<< orphan*/  lo_disk; } ;
struct kobject {int dummy; } ;
typedef  int dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kobject* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MINORMASK ; 
 struct kobject* get_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_devices_mutex ; 
 struct loop_device* loop_init_one (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kobject *loop_probe(dev_t dev, int *part, void *data)
{
	struct loop_device *lo;
	struct kobject *kobj;

	mutex_lock(&loop_devices_mutex);
	lo = loop_init_one(dev & MINORMASK);
	kobj = lo ? get_disk(lo->lo_disk) : ERR_PTR(-ENOMEM);
	mutex_unlock(&loop_devices_mutex);

	*part = 0;
	return kobj;
}