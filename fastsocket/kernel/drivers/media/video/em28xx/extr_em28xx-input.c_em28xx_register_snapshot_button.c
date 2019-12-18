#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int version; void* product; void* vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int* evbit; TYPE_3__ dev; TYPE_2__ id; scalar_t__ keycodemax; scalar_t__ keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  phys; } ;
struct em28xx {int /*<<< orphan*/  sbutton_query_work; struct input_dev* sbutton_input_dev; TYPE_4__* udev; int /*<<< orphan*/  snapshot_button_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_USB ; 
 int /*<<< orphan*/  EM28XX_SBUTTON_QUERY_INTERVAL ; 
 int /*<<< orphan*/  EM28XX_SNAPSHOT_KEY ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_errdev (char*) ; 
 int /*<<< orphan*/  em28xx_info (char*) ; 
 int /*<<< orphan*/  em28xx_query_sbutton ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void em28xx_register_snapshot_button(struct em28xx *dev)
{
	struct input_dev *input_dev;
	int err;

	em28xx_info("Registering snapshot button...\n");
	input_dev = input_allocate_device();
	if (!input_dev) {
		em28xx_errdev("input_allocate_device failed\n");
		return;
	}

	usb_make_path(dev->udev, dev->snapshot_button_path,
		      sizeof(dev->snapshot_button_path));
	strlcat(dev->snapshot_button_path, "/sbutton",
		sizeof(dev->snapshot_button_path));
	INIT_DELAYED_WORK(&dev->sbutton_query_work, em28xx_query_sbutton);

	input_dev->name = "em28xx snapshot button";
	input_dev->phys = dev->snapshot_button_path;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	set_bit(EM28XX_SNAPSHOT_KEY, input_dev->keybit);
	input_dev->keycodesize = 0;
	input_dev->keycodemax = 0;
	input_dev->id.bustype = BUS_USB;
	input_dev->id.vendor = le16_to_cpu(dev->udev->descriptor.idVendor);
	input_dev->id.product = le16_to_cpu(dev->udev->descriptor.idProduct);
	input_dev->id.version = 1;
	input_dev->dev.parent = &dev->udev->dev;

	err = input_register_device(input_dev);
	if (err) {
		em28xx_errdev("input_register_device failed\n");
		input_free_device(input_dev);
		return;
	}

	dev->sbutton_input_dev = input_dev;
	schedule_delayed_work(&dev->sbutton_query_work,
			      msecs_to_jiffies(EM28XX_SBUTTON_QUERY_INTERVAL));
	return;

}