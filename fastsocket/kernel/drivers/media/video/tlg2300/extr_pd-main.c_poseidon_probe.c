#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* driver; } ;
struct usb_interface {struct device dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct poseidon {int /*<<< orphan*/  pm_work; TYPE_3__* udev; int /*<<< orphan*/  device_list; TYPE_2__ v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  interface; int /*<<< orphan*/  kref; } ;
struct TYPE_6__ {int autosuspend_delay; scalar_t__ autosuspend_disabled; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PM_SUSPEND_DELAY ; 
 int /*<<< orphan*/  check_firmware (struct usb_device*,int*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct poseidon* find_old_poseidon (struct usb_device*) ; 
 int /*<<< orphan*/  hibernation_resume ; 
 scalar_t__ in_hibernation (struct poseidon*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct poseidon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logpm (struct poseidon*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_device_list ; 
 int /*<<< orphan*/  pd_dvb_usb_device_init (struct poseidon*) ; 
 int pd_video_init (struct poseidon*) ; 
 int /*<<< orphan*/  poseidon_audio_init (struct poseidon*) ; 
 int /*<<< orphan*/  poseidon_fm_init (struct poseidon*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_map_flags (struct poseidon*,struct usb_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 TYPE_3__* usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct poseidon*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int poseidon_probe(struct usb_interface *interface,
				const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct poseidon *pd = NULL;
	int ret = 0;
	int new_one = 0;

	/* download firmware */
	check_firmware(udev, &ret);
	if (ret)
		return 0;

	/* Do I recovery from the hibernate ? */
	pd = find_old_poseidon(udev);
	if (!pd) {
		pd = kzalloc(sizeof(*pd), GFP_KERNEL);
		if (!pd)
			return -ENOMEM;
		kref_init(&pd->kref);
		set_map_flags(pd, udev);
		new_one = 1;
	}

	pd->udev	= usb_get_dev(udev);
	pd->interface	= usb_get_intf(interface);
	usb_set_intfdata(interface, pd);

	if (new_one) {
		struct device *dev = &interface->dev;

		logpm(pd);
		mutex_init(&pd->lock);

		/* register v4l2 device */
		snprintf(pd->v4l2_dev.name, sizeof(pd->v4l2_dev.name), "%s %s",
			dev->driver->name, dev_name(dev));
		ret = v4l2_device_register(NULL, &pd->v4l2_dev);

		/* register devices in directory /dev */
		ret = pd_video_init(pd);
		poseidon_audio_init(pd);
		poseidon_fm_init(pd);
		pd_dvb_usb_device_init(pd);

		INIT_LIST_HEAD(&pd->device_list);
		list_add_tail(&pd->device_list, &pd_device_list);
	}

	device_init_wakeup(&udev->dev, 1);
#ifdef CONFIG_PM
	pd->udev->autosuspend_delay = HZ * PM_SUSPEND_DELAY;
	pd->udev->autosuspend_disabled = 0;

	if (in_hibernation(pd)) {
		INIT_WORK(&pd->pm_work, hibernation_resume);
		schedule_work(&pd->pm_work);
	}
#endif
	return 0;
}