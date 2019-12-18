#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  sem; TYPE_6__* bus; TYPE_4__* type; TYPE_2__* class; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_12__ {TYPE_5__* pm; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* complete ) (struct device*) ;} ;
struct TYPE_10__ {TYPE_3__* pm; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* complete ) (struct device*) ;} ;
struct TYPE_8__ {TYPE_1__* pm; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* complete ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_dev_dbg (struct device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 
 int /*<<< orphan*/  stub3 (struct device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_complete(struct device *dev, pm_message_t state)
{
	down(&dev->sem);

	if (dev->class && dev->class->pm && dev->class->pm->complete) {
		pm_dev_dbg(dev, state, "completing class ");
		dev->class->pm->complete(dev);
	}

	if (dev->type && dev->type->pm && dev->type->pm->complete) {
		pm_dev_dbg(dev, state, "completing type ");
		dev->type->pm->complete(dev);
	}

	if (dev->bus && dev->bus->pm && dev->bus->pm->complete) {
		pm_dev_dbg(dev, state, "completing ");
		dev->bus->pm->complete(dev);
	}

	up(&dev->sem);
}