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
struct kobject {int dummy; } ;
struct brd_device {int /*<<< orphan*/  brd_disk; } ;
typedef  int dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kobject* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MINORMASK ; 
 int /*<<< orphan*/  brd_devices_mutex ; 
 struct brd_device* brd_init_one (int) ; 
 struct kobject* get_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kobject *brd_probe(dev_t dev, int *part, void *data)
{
	struct brd_device *brd;
	struct kobject *kobj;

	mutex_lock(&brd_devices_mutex);
	brd = brd_init_one(dev & MINORMASK);
	kobj = brd ? get_disk(brd->brd_disk) : ERR_PTR(-ENOMEM);
	mutex_unlock(&brd_devices_mutex);

	*part = 0;
	return kobj;
}