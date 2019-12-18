#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct hid_device {TYPE_2__ dev; int /*<<< orphan*/  debug_list; int /*<<< orphan*/  debug_wait; TYPE_1__* report_enum; int /*<<< orphan*/  collection_size; int /*<<< orphan*/ * collection; } ;
struct hid_collection {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  report_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hid_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_DEFAULT_NUM_COLLECTIONS ; 
 unsigned int HID_REPORT_TYPES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  hid_bus_type ; 
 int /*<<< orphan*/  hid_device_release ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct hid_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 

struct hid_device *hid_allocate_device(void)
{
	struct hid_device *hdev;
	unsigned int i;
	int ret = -ENOMEM;

	hdev = kzalloc(sizeof(*hdev), GFP_KERNEL);
	if (hdev == NULL)
		return ERR_PTR(ret);

	device_initialize(&hdev->dev);
	hdev->dev.release = hid_device_release;
	hdev->dev.bus = &hid_bus_type;

	hdev->collection = kcalloc(HID_DEFAULT_NUM_COLLECTIONS,
			sizeof(struct hid_collection), GFP_KERNEL);
	if (hdev->collection == NULL)
		goto err;
	hdev->collection_size = HID_DEFAULT_NUM_COLLECTIONS;

	for (i = 0; i < HID_REPORT_TYPES; i++)
		INIT_LIST_HEAD(&hdev->report_enum[i].report_list);

	init_waitqueue_head(&hdev->debug_wait);
	INIT_LIST_HEAD(&hdev->debug_list);

	return hdev;
err:
	put_device(&hdev->dev);
	return ERR_PTR(ret);
}