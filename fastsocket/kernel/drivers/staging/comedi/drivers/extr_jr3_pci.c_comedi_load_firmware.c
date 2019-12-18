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
struct jr3_pci_dev_private {TYPE_1__* pci_dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct comedi_device {struct jr3_pci_dev_private* private; } ;
typedef  int (* comedi_firmware_callback ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int comedi_load_firmware(struct comedi_device *dev, char *name,
				comedi_firmware_callback cb)
{
	int result = 0;
	const struct firmware *fw;
	char *firmware_path;
	static const char *prefix = "comedi/";
	struct jr3_pci_dev_private *devpriv = dev->private;

	firmware_path = kmalloc(strlen(prefix) + strlen(name) + 1, GFP_KERNEL);
	if (!firmware_path) {
		result = -ENOMEM;
	} else {
		firmware_path[0] = '\0';
		strcat(firmware_path, prefix);
		strcat(firmware_path, name);
		result = request_firmware(&fw, firmware_path,
					  &devpriv->pci_dev->dev);
		if (result == 0) {
			if (!cb)
				result = -EINVAL;
			else
				result = cb(dev, fw->data, fw->size);
			release_firmware(fw);
		}
		kfree(firmware_path);
	}
	return result;
}