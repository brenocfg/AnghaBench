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
typedef  int u16 ;
struct wm8350_platform_data {int (* init ) (struct wm8350*) ;scalar_t__ irq_high; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_12__ {int rev_g_coeff; int /*<<< orphan*/  pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_11__ {void* max_isink; void* max_dcdc; } ;
struct wm8350 {int (* read_dev ) (struct wm8350*,int /*<<< orphan*/ ,int,int*) ;int chip_irq; int /*<<< orphan*/  reg_cache; TYPE_3__ wdt; TYPE_2__ rtc; TYPE_5__ power; TYPE_1__ hwmon; TYPE_7__ gpio; TYPE_6__ codec; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_mutex; int /*<<< orphan*/  auxadc_mutex; TYPE_4__ pmic; } ;
typedef  int /*<<< orphan*/  mask_rev ;
typedef  int /*<<< orphan*/  id2 ;
typedef  int /*<<< orphan*/  id1 ;

/* Variables and functions */
 int ENODEV ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int WM8350_CHIP_REV_MASK ; 
 int /*<<< orphan*/  WM8350_COMPARATOR_INT_STATUS_MASK ; 
 int WM8350_CONF_STS_MASK ; 
 int WM8350_CUST_ID_MASK ; 
 void* WM8350_DCDC_4 ; 
 void* WM8350_DCDC_6 ; 
 int /*<<< orphan*/  WM8350_GPIO_INT_STATUS_MASK ; 
 int /*<<< orphan*/  WM8350_ID ; 
 int /*<<< orphan*/  WM8350_INT_STATUS_1_MASK ; 
 int /*<<< orphan*/  WM8350_INT_STATUS_2_MASK ; 
 int /*<<< orphan*/  WM8350_IRQ_POL ; 
 void* WM8350_ISINK_A ; 
 void* WM8350_ISINK_B ; 
 int /*<<< orphan*/  WM8350_RESET_ID ; 
 int /*<<< orphan*/  WM8350_REVISION ; 
#define  WM8350_REV_E 131 
#define  WM8350_REV_F 130 
#define  WM8350_REV_G 129 
#define  WM8350_REV_H 128 
 int /*<<< orphan*/  WM8350_SYSTEM_CONTROL_1 ; 
 int /*<<< orphan*/  WM8350_SYSTEM_INTERRUPTS_MASK ; 
 int /*<<< orphan*/  WM8350_UNDER_VOLTAGE_INT_STATUS_MASK ; 
 int be16_to_cpu (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm8350*) ; 
 int stub1 (struct wm8350*,int /*<<< orphan*/ ,int,int*) ; 
 int stub2 (struct wm8350*,int /*<<< orphan*/ ,int,int*) ; 
 int stub3 (struct wm8350*,int /*<<< orphan*/ ,int,int*) ; 
 int stub4 (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_client_dev_register (struct wm8350*,char*,int /*<<< orphan*/ *) ; 
 int wm8350_create_cache (struct wm8350*,int,int) ; 
 int /*<<< orphan*/  wm8350_irq ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wm8350_device_init(struct wm8350 *wm8350, int irq,
		       struct wm8350_platform_data *pdata)
{
	int ret;
	u16 id1, id2, mask_rev;
	u16 cust_id, mode, chip_rev;

	/* get WM8350 revision and config mode */
	ret = wm8350->read_dev(wm8350, WM8350_RESET_ID, sizeof(id1), &id1);
	if (ret != 0) {
		dev_err(wm8350->dev, "Failed to read ID: %d\n", ret);
		goto err;
	}

	ret = wm8350->read_dev(wm8350, WM8350_ID, sizeof(id2), &id2);
	if (ret != 0) {
		dev_err(wm8350->dev, "Failed to read ID: %d\n", ret);
		goto err;
	}

	ret = wm8350->read_dev(wm8350, WM8350_REVISION, sizeof(mask_rev),
			       &mask_rev);
	if (ret != 0) {
		dev_err(wm8350->dev, "Failed to read revision: %d\n", ret);
		goto err;
	}

	id1 = be16_to_cpu(id1);
	id2 = be16_to_cpu(id2);
	mask_rev = be16_to_cpu(mask_rev);

	if (id1 != 0x6143) {
		dev_err(wm8350->dev,
			"Device with ID %x is not a WM8350\n", id1);
		ret = -ENODEV;
		goto err;
	}

	mode = id2 & WM8350_CONF_STS_MASK >> 10;
	cust_id = id2 & WM8350_CUST_ID_MASK;
	chip_rev = (id2 & WM8350_CHIP_REV_MASK) >> 12;
	dev_info(wm8350->dev,
		 "CONF_STS %d, CUST_ID %d, MASK_REV %d, CHIP_REV %d\n",
		 mode, cust_id, mask_rev, chip_rev);

	if (cust_id != 0) {
		dev_err(wm8350->dev, "Unsupported CUST_ID\n");
		ret = -ENODEV;
		goto err;
	}

	switch (mask_rev) {
	case 0:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		switch (chip_rev) {
		case WM8350_REV_E:
			dev_info(wm8350->dev, "WM8350 Rev E\n");
			break;
		case WM8350_REV_F:
			dev_info(wm8350->dev, "WM8350 Rev F\n");
			break;
		case WM8350_REV_G:
			dev_info(wm8350->dev, "WM8350 Rev G\n");
			wm8350->power.rev_g_coeff = 1;
			break;
		case WM8350_REV_H:
			dev_info(wm8350->dev, "WM8350 Rev H\n");
			wm8350->power.rev_g_coeff = 1;
			break;
		default:
			/* For safety we refuse to run on unknown hardware */
			dev_err(wm8350->dev, "Unknown WM8350 CHIP_REV\n");
			ret = -ENODEV;
			goto err;
		}
		break;

	case 1:
		wm8350->pmic.max_dcdc = WM8350_DCDC_4;
		wm8350->pmic.max_isink = WM8350_ISINK_A;

		switch (chip_rev) {
		case 0:
			dev_info(wm8350->dev, "WM8351 Rev A\n");
			wm8350->power.rev_g_coeff = 1;
			break;

		case 1:
			dev_info(wm8350->dev, "WM8351 Rev B\n");
			wm8350->power.rev_g_coeff = 1;
			break;

		default:
			dev_err(wm8350->dev, "Unknown WM8351 CHIP_REV\n");
			ret = -ENODEV;
			goto err;
		}
		break;

	case 2:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		switch (chip_rev) {
		case 0:
			dev_info(wm8350->dev, "WM8352 Rev A\n");
			wm8350->power.rev_g_coeff = 1;
			break;

		default:
			dev_err(wm8350->dev, "Unknown WM8352 CHIP_REV\n");
			ret = -ENODEV;
			goto err;
		}
		break;

	default:
		dev_err(wm8350->dev, "Unknown MASK_REV\n");
		ret = -ENODEV;
		goto err;
	}

	ret = wm8350_create_cache(wm8350, mask_rev, mode);
	if (ret < 0) {
		dev_err(wm8350->dev, "Failed to create register cache\n");
		return ret;
	}

	wm8350_reg_write(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0xFFFF);
	wm8350_reg_write(wm8350, WM8350_INT_STATUS_1_MASK, 0xFFFF);
	wm8350_reg_write(wm8350, WM8350_INT_STATUS_2_MASK, 0xFFFF);
	wm8350_reg_write(wm8350, WM8350_UNDER_VOLTAGE_INT_STATUS_MASK, 0xFFFF);
	wm8350_reg_write(wm8350, WM8350_GPIO_INT_STATUS_MASK, 0xFFFF);
	wm8350_reg_write(wm8350, WM8350_COMPARATOR_INT_STATUS_MASK, 0xFFFF);

	mutex_init(&wm8350->auxadc_mutex);
	mutex_init(&wm8350->irq_mutex);
	if (irq) {
		int flags = IRQF_ONESHOT;

		if (pdata && pdata->irq_high) {
			flags |= IRQF_TRIGGER_HIGH;

			wm8350_set_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
					WM8350_IRQ_POL);
		} else {
			flags |= IRQF_TRIGGER_LOW;

			wm8350_clear_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
					  WM8350_IRQ_POL);
		}

		ret = request_threaded_irq(irq, NULL, wm8350_irq, flags,
					   "wm8350", wm8350);
		if (ret != 0) {
			dev_err(wm8350->dev, "Failed to request IRQ: %d\n",
				ret);
			goto err;
		}
	} else {
		dev_err(wm8350->dev, "No IRQ configured\n");
		goto err;
	}
	wm8350->chip_irq = irq;

	if (pdata && pdata->init) {
		ret = pdata->init(wm8350);
		if (ret != 0) {
			dev_err(wm8350->dev, "Platform init() failed: %d\n",
				ret);
			goto err;
		}
	}

	wm8350_reg_write(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0x0);

	wm8350_client_dev_register(wm8350, "wm8350-codec",
				   &(wm8350->codec.pdev));
	wm8350_client_dev_register(wm8350, "wm8350-gpio",
				   &(wm8350->gpio.pdev));
	wm8350_client_dev_register(wm8350, "wm8350-hwmon",
				   &(wm8350->hwmon.pdev));
	wm8350_client_dev_register(wm8350, "wm8350-power",
				   &(wm8350->power.pdev));
	wm8350_client_dev_register(wm8350, "wm8350-rtc", &(wm8350->rtc.pdev));
	wm8350_client_dev_register(wm8350, "wm8350-wdt", &(wm8350->wdt.pdev));

	return 0;

err:
	kfree(wm8350->reg_cache);
	return ret;
}