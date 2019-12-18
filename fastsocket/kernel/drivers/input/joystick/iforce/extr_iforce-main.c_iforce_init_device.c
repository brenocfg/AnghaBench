#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int vendor; int product; int /*<<< orphan*/  bustype; } ;
struct TYPE_14__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* name; int* evbit; struct ff_device* ff; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  keybit; TYPE_4__ id; TYPE_7__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct TYPE_12__ {char* name; int end; int /*<<< orphan*/ * sibling; int /*<<< orphan*/ * child; int /*<<< orphan*/ * parent; int /*<<< orphan*/  flags; scalar_t__ start; } ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
struct iforce {int bus; int* edata; struct input_dev* dev; TYPE_6__* type; int /*<<< orphan*/  ecmd; TYPE_5__ device_memory; TYPE_3__* serio; TYPE_2__* usbdev; int /*<<< orphan*/  xmit_data; TYPE_1__ xmit; int /*<<< orphan*/  mem_mutex; int /*<<< orphan*/  xmit_lock; int /*<<< orphan*/  wait; } ;
struct ff_device {int /*<<< orphan*/  playback; int /*<<< orphan*/  (* set_autocenter ) (struct input_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  set_gain; int /*<<< orphan*/  erase; int /*<<< orphan*/  upload; } ;
struct TYPE_13__ {int idvendor; int idproduct; char* name; scalar_t__* btn; short* abs; scalar_t__* ff; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ABS_BRAKE 140 
#define  ABS_GAS 139 
#define  ABS_HAT0X 138 
#define  ABS_HAT0Y 137 
#define  ABS_HAT1X 136 
#define  ABS_HAT1Y 135 
#define  ABS_RUDDER 134 
#define  ABS_THROTTLE 133 
#define  ABS_WHEEL 132 
#define  ABS_X 131 
#define  ABS_Y 130 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 short BTN_DEAD ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int /*<<< orphan*/  BUS_USB ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_FF_STATUS ; 
 int /*<<< orphan*/  EV_KEY ; 
#define  IFORCE_232 129 
 int IFORCE_EFFECTS_MAX ; 
#define  IFORCE_USB 128 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_warn (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  err (char*) ; 
 TYPE_6__* iforce_device ; 
 int /*<<< orphan*/  iforce_dump_packet (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iforce_erase_effect ; 
 int /*<<< orphan*/  iforce_get_id_packet (struct iforce*,...) ; 
 int /*<<< orphan*/  iforce_open ; 
 int /*<<< orphan*/  iforce_playback ; 
 int /*<<< orphan*/  iforce_release ; 
 int /*<<< orphan*/  iforce_set_autocenter (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iforce_set_gain ; 
 int /*<<< orphan*/  iforce_upload_effect ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct input_dev* input_allocate_device () ; 
 int input_ff_create (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,short,int,int,int,int) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct iforce*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iforce_init_device(struct iforce *iforce)
{
	struct input_dev *input_dev;
	struct ff_device *ff;
	unsigned char c[] = "CEOV";
	int i, error;
	int ff_effects = 0;

	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	init_waitqueue_head(&iforce->wait);
	spin_lock_init(&iforce->xmit_lock);
	mutex_init(&iforce->mem_mutex);
	iforce->xmit.buf = iforce->xmit_data;
	iforce->dev = input_dev;

/*
 * Input device fields.
 */

	switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
	case IFORCE_USB:
		input_dev->id.bustype = BUS_USB;
		input_dev->dev.parent = &iforce->usbdev->dev;
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_232
	case IFORCE_232:
		input_dev->id.bustype = BUS_RS232;
		input_dev->dev.parent = &iforce->serio->dev;
		break;
#endif
	}

	input_set_drvdata(input_dev, iforce);

	input_dev->name = "Unknown I-Force device";
	input_dev->open = iforce_open;
	input_dev->close = iforce_release;

/*
 * On-device memory allocation.
 */

	iforce->device_memory.name = "I-Force device effect memory";
	iforce->device_memory.start = 0;
	iforce->device_memory.end = 200;
	iforce->device_memory.flags = IORESOURCE_MEM;
	iforce->device_memory.parent = NULL;
	iforce->device_memory.child = NULL;
	iforce->device_memory.sibling = NULL;

/*
 * Wait until device ready - until it sends its first response.
 */

	for (i = 0; i < 20; i++)
		if (!iforce_get_id_packet(iforce, "O"))
			break;

	if (i == 20) { /* 5 seconds */
		err("Timeout waiting for response from device.");
		error = -ENODEV;
		goto fail;
	}

/*
 * Get device info.
 */

	if (!iforce_get_id_packet(iforce, "M"))
		input_dev->id.vendor = (iforce->edata[2] << 8) | iforce->edata[1];
	else
		dev_warn(&iforce->dev->dev, "Device does not respond to id packet M\n");

	if (!iforce_get_id_packet(iforce, "P"))
		input_dev->id.product = (iforce->edata[2] << 8) | iforce->edata[1];
	else
		dev_warn(&iforce->dev->dev, "Device does not respond to id packet P\n");

	if (!iforce_get_id_packet(iforce, "B"))
		iforce->device_memory.end = (iforce->edata[2] << 8) | iforce->edata[1];
	else
		dev_warn(&iforce->dev->dev, "Device does not respond to id packet B\n");

	if (!iforce_get_id_packet(iforce, "N"))
		ff_effects = iforce->edata[1];
	else
		dev_warn(&iforce->dev->dev, "Device does not respond to id packet N\n");

	/* Check if the device can store more effects than the driver can really handle */
	if (ff_effects > IFORCE_EFFECTS_MAX) {
		dev_warn(&iforce->dev->dev, "Limiting number of effects to %d (device reports %d)\n",
		       IFORCE_EFFECTS_MAX, ff_effects);
		ff_effects = IFORCE_EFFECTS_MAX;
	}

/*
 * Display additional info.
 */

	for (i = 0; c[i]; i++)
		if (!iforce_get_id_packet(iforce, c + i))
			iforce_dump_packet("info", iforce->ecmd, iforce->edata);

/*
 * Disable spring, enable force feedback.
 */
	iforce_set_autocenter(input_dev, 0);

/*
 * Find appropriate device entry
 */

	for (i = 0; iforce_device[i].idvendor; i++)
		if (iforce_device[i].idvendor == input_dev->id.vendor &&
		    iforce_device[i].idproduct == input_dev->id.product)
			break;

	iforce->type = iforce_device + i;
	input_dev->name = iforce->type->name;

/*
 * Set input device bitfields and ranges.
 */

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) |
		BIT_MASK(EV_FF_STATUS);

	for (i = 0; iforce->type->btn[i] >= 0; i++)
		set_bit(iforce->type->btn[i], input_dev->keybit);
	set_bit(BTN_DEAD, input_dev->keybit);

	for (i = 0; iforce->type->abs[i] >= 0; i++) {

		signed short t = iforce->type->abs[i];

		switch (t) {

			case ABS_X:
			case ABS_Y:
			case ABS_WHEEL:

				input_set_abs_params(input_dev, t, -1920, 1920, 16, 128);
				set_bit(t, input_dev->ffbit);
				break;

			case ABS_THROTTLE:
			case ABS_GAS:
			case ABS_BRAKE:

				input_set_abs_params(input_dev, t, 0, 255, 0, 0);
				break;

			case ABS_RUDDER:

				input_set_abs_params(input_dev, t, -128, 127, 0, 0);
				break;

			case ABS_HAT0X:
			case ABS_HAT0Y:
		        case ABS_HAT1X:
		        case ABS_HAT1Y:

				input_set_abs_params(input_dev, t, -1, 1, 0, 0);
				break;
		}
	}

	if (ff_effects) {

		for (i = 0; iforce->type->ff[i] >= 0; i++)
			set_bit(iforce->type->ff[i], input_dev->ffbit);

		error = input_ff_create(input_dev, ff_effects);
		if (error)
			goto fail;

		ff = input_dev->ff;
		ff->upload = iforce_upload_effect;
		ff->erase = iforce_erase_effect;
		ff->set_gain = iforce_set_gain;
		ff->set_autocenter = iforce_set_autocenter;
		ff->playback = iforce_playback;
	}
/*
 * Register input device.
 */

	error = input_register_device(iforce->dev);
	if (error)
		goto fail;

	return 0;

 fail:	input_free_device(input_dev);
	return error;
}