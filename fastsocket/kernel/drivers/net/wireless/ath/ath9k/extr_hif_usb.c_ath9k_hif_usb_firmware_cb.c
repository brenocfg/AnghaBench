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
struct hif_device_usb {int /*<<< orphan*/ * htc_handle; int /*<<< orphan*/  fw_done; int /*<<< orphan*/  flags; TYPE_3__* usb_device_id; TYPE_2__* udev; TYPE_1__* interface; int /*<<< orphan*/  fw_size; int /*<<< orphan*/  fw_data; int /*<<< orphan*/  fw_name; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver_info; int /*<<< orphan*/  idProduct; } ;
struct TYPE_5__ {int /*<<< orphan*/  product; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIF_USB_READY ; 
 int /*<<< orphan*/  ath9k_hif_usb_dev_deinit (struct hif_device_usb*) ; 
 int ath9k_hif_usb_dev_init (struct hif_device_usb*) ; 
 int /*<<< orphan*/  ath9k_hif_usb_firmware_fail (struct hif_device_usb*) ; 
 int /*<<< orphan*/ * ath9k_htc_hw_alloc (struct hif_device_usb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_htc_hw_free (int /*<<< orphan*/ *) ; 
 int ath9k_htc_hw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_usb ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void ath9k_hif_usb_firmware_cb(const struct firmware *fw, void *context)
{
	struct hif_device_usb *hif_dev = context;
	int ret;

	if (!fw) {
		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Failed to get firmware %s\n",
			hif_dev->fw_name);
		goto err_fw;
	}

	hif_dev->htc_handle = ath9k_htc_hw_alloc(hif_dev, &hif_usb,
						 &hif_dev->udev->dev);
	if (hif_dev->htc_handle == NULL)
		goto err_dev_alloc;

	hif_dev->fw_data = fw->data;
	hif_dev->fw_size = fw->size;

	/* Proceed with initialization */

	ret = ath9k_hif_usb_dev_init(hif_dev);
	if (ret)
		goto err_dev_init;

	ret = ath9k_htc_hw_init(hif_dev->htc_handle,
				&hif_dev->interface->dev,
				hif_dev->usb_device_id->idProduct,
				hif_dev->udev->product,
				hif_dev->usb_device_id->driver_info);
	if (ret) {
		ret = -EINVAL;
		goto err_htc_hw_init;
	}

	release_firmware(fw);
	hif_dev->flags |= HIF_USB_READY;
	complete(&hif_dev->fw_done);

	return;

err_htc_hw_init:
	ath9k_hif_usb_dev_deinit(hif_dev);
err_dev_init:
	ath9k_htc_hw_free(hif_dev->htc_handle);
err_dev_alloc:
	release_firmware(fw);
err_fw:
	ath9k_hif_usb_firmware_fail(hif_dev);
}