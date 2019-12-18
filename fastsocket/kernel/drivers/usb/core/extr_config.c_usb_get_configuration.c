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
struct usb_host_config {int dummy; } ;
struct TYPE_2__ {int bNumConfigurations; } ;
struct device {int dummy; } ;
struct usb_device {scalar_t__ authorized; unsigned char** rawdescriptors; TYPE_1__ descriptor; int /*<<< orphan*/ * config; struct device dev; } ;
struct usb_config_descriptor {int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_DT_CONFIG ; 
 unsigned int USB_DT_CONFIG_SIZE ; 
 int USB_MAXCONFIG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int max (int,unsigned int) ; 
 int usb_get_descriptor (struct usb_device*,int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int usb_parse_configuration (struct device*,unsigned int,int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

int usb_get_configuration(struct usb_device *dev)
{
	struct device *ddev = &dev->dev;
	int ncfg = dev->descriptor.bNumConfigurations;
	int result = 0;
	unsigned int cfgno, length;
	unsigned char *buffer;
	unsigned char *bigbuffer;
	struct usb_config_descriptor *desc;

	cfgno = 0;
	if (dev->authorized == 0)	/* Not really an error */
		goto out_not_authorized;
	result = -ENOMEM;
	if (ncfg > USB_MAXCONFIG) {
		dev_warn(ddev, "too many configurations: %d, "
		    "using maximum allowed: %d\n", ncfg, USB_MAXCONFIG);
		dev->descriptor.bNumConfigurations = ncfg = USB_MAXCONFIG;
	}

	if (ncfg < 1) {
		dev_err(ddev, "no configurations\n");
		return -EINVAL;
	}

	length = ncfg * sizeof(struct usb_host_config);
	dev->config = kzalloc(length, GFP_KERNEL);
	if (!dev->config)
		goto err2;

	length = ncfg * sizeof(char *);
	dev->rawdescriptors = kzalloc(length, GFP_KERNEL);
	if (!dev->rawdescriptors)
		goto err2;

	buffer = kmalloc(USB_DT_CONFIG_SIZE, GFP_KERNEL);
	if (!buffer)
		goto err2;
	desc = (struct usb_config_descriptor *)buffer;

	result = 0;
	for (; cfgno < ncfg; cfgno++) {
		/* We grab just the first descriptor so we know how long
		 * the whole configuration is */
		result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno,
		    buffer, USB_DT_CONFIG_SIZE);
		if (result < 0) {
			dev_err(ddev, "unable to read config index %d "
			    "descriptor/%s: %d\n", cfgno, "start", result);
			if (result != -EPIPE)
				goto err;
			dev_err(ddev, "chopping to %d config(s)\n", cfgno);
			dev->descriptor.bNumConfigurations = cfgno;
			break;
		} else if (result < 4) {
			dev_err(ddev, "config index %d descriptor too short "
			    "(expected %i, got %i)\n", cfgno,
			    USB_DT_CONFIG_SIZE, result);
			result = -EINVAL;
			goto err;
		}
		length = max((int) le16_to_cpu(desc->wTotalLength),
		    USB_DT_CONFIG_SIZE);

		/* Now that we know the length, get the whole thing */
		bigbuffer = kmalloc(length, GFP_KERNEL);
		if (!bigbuffer) {
			result = -ENOMEM;
			goto err;
		}
		result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno,
		    bigbuffer, length);
		if (result < 0) {
			dev_err(ddev, "unable to read config index %d "
			    "descriptor/%s\n", cfgno, "all");
			kfree(bigbuffer);
			goto err;
		}
		if (result < length) {
			dev_warn(ddev, "config index %d descriptor too short "
			    "(expected %i, got %i)\n", cfgno, length, result);
			length = result;
		}

		dev->rawdescriptors[cfgno] = bigbuffer;

		result = usb_parse_configuration(&dev->dev, cfgno,
		    &dev->config[cfgno], bigbuffer, length);
		if (result < 0) {
			++cfgno;
			goto err;
		}
	}
	result = 0;

err:
	kfree(buffer);
out_not_authorized:
	dev->descriptor.bNumConfigurations = cfgno;
err2:
	if (result == -ENOMEM)
		dev_err(ddev, "out of memory\n");
	return result;
}