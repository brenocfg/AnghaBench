#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  release; } ;
struct uwb_dev {int /*<<< orphan*/  streams; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  dev_addr; TYPE_1__ dev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_GLOBAL_STREAMS ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_addr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_sys_release ; 
 int /*<<< orphan*/  uwb_mac_addr_init (int /*<<< orphan*/ *) ; 

void uwb_dev_init(struct uwb_dev *uwb_dev)
{
	mutex_init(&uwb_dev->mutex);
	device_initialize(&uwb_dev->dev);
	uwb_dev->dev.release = uwb_dev_sys_release;
	uwb_dev_addr_init(&uwb_dev->dev_addr);
	uwb_mac_addr_init(&uwb_dev->mac_addr);
	bitmap_fill(uwb_dev->streams, UWB_NUM_GLOBAL_STREAMS);
}