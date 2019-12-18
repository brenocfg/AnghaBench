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
struct rt2x00_dev {int /*<<< orphan*/  flags; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int (* initialize ) (struct rt2x00_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_INITIALIZED ; 
 int rt2x00queue_initialize (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_uninitialize (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct rt2x00_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2x00lib_initialize(struct rt2x00_dev *rt2x00dev)
{
	int status;

	if (test_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags))
		return 0;

	/*
	 * Allocate all queue entries.
	 */
	status = rt2x00queue_initialize(rt2x00dev);
	if (status)
		return status;

	/*
	 * Initialize the device.
	 */
	status = rt2x00dev->ops->lib->initialize(rt2x00dev);
	if (status) {
		rt2x00queue_uninitialize(rt2x00dev);
		return status;
	}

	set_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags);

	return 0;
}