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
typedef  int u8 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* max_brightness; void* brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 void* HW_LEVEL_MAX ; 
 void* HW_LEVEL_MIN ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AL_M1533 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AL_M7101 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AL ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  SB_MPS1 ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (void*) ; 
 void* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 void* pmu_dev ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  progearbl_ops ; 
 int /*<<< orphan*/  progearbl_set_intensity (struct backlight_device*) ; 
 void* sb_dev ; 

__attribute__((used)) static int progearbl_probe(struct platform_device *pdev)
{
	u8 temp;
	struct backlight_device *progear_backlight_device;

	pmu_dev = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M7101, NULL);
	if (!pmu_dev) {
		printk("ALI M7101 PMU not found.\n");
		return -ENODEV;
	}

	sb_dev = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533, NULL);
	if (!sb_dev) {
		printk("ALI 1533 SB not found.\n");
		pci_dev_put(pmu_dev);
		return -ENODEV;
	}

	/*     Set SB_MPS1 to enable brightness control. */
	pci_read_config_byte(sb_dev, SB_MPS1, &temp);
	pci_write_config_byte(sb_dev, SB_MPS1, temp | 0x20);

	progear_backlight_device = backlight_device_register("progear-bl",
							     &pdev->dev, NULL,
							     &progearbl_ops);
	if (IS_ERR(progear_backlight_device))
		return PTR_ERR(progear_backlight_device);

	platform_set_drvdata(pdev, progear_backlight_device);

	progear_backlight_device->props.power = FB_BLANK_UNBLANK;
	progear_backlight_device->props.brightness = HW_LEVEL_MAX - HW_LEVEL_MIN;
	progear_backlight_device->props.max_brightness = HW_LEVEL_MAX - HW_LEVEL_MIN;
	progearbl_set_intensity(progear_backlight_device);

	return 0;
}