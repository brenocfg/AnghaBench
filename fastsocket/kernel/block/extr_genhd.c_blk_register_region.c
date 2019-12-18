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
struct module {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_map ; 
 int /*<<< orphan*/  kobj_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,struct module*,struct kobject* (*) (int /*<<< orphan*/ ,int*,void*),int (*) (int /*<<< orphan*/ ,void*),void*) ; 

void blk_register_region(dev_t devt, unsigned long range, struct module *module,
			 struct kobject *(*probe)(dev_t, int *, void *),
			 int (*lock)(dev_t, void *), void *data)
{
	kobj_map(bdev_map, devt, range, module, probe, lock, data);
}