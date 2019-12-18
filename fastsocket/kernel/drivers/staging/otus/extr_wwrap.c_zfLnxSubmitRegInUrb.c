#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct usbdrv_private {int /*<<< orphan*/  regUsbReadBuf; int /*<<< orphan*/  udev; int /*<<< orphan*/  RegInUrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_REG_IN_PIPE ; 
 int /*<<< orphan*/  ZM_USB_REG_MAX_BUF_SIZE ; 
 int /*<<< orphan*/  zfLnxUsbRegIn_callback ; 
 int /*<<< orphan*/  zfLnxUsbSubmitIntUrb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

u32_t zfLnxSubmitRegInUrb(zdev_t *dev)
{
    u32_t ret;
    struct usbdrv_private *macp = dev->ml_priv;

    /* Submit a rx urb */
    //ret = zfLnxUsbSubmitBulkUrb(macp->RegInUrb, macp->udev,
    //        USB_REG_IN_PIPE, USB_DIR_IN, macp->regUsbReadBuf,
    //        ZM_USB_REG_MAX_BUF_SIZE, zfLnxUsbRegIn_callback, dev);
    //CWYang(-)
    //if (ret != 0)
    //    printk("zfwUsbSubmitBulkUrb fail, status: 0x%08x\n", (int)ret);

    ret = zfLnxUsbSubmitIntUrb(macp->RegInUrb, macp->udev,
            USB_REG_IN_PIPE, USB_DIR_IN, macp->regUsbReadBuf,
            ZM_USB_REG_MAX_BUF_SIZE, zfLnxUsbRegIn_callback, dev, 1);

    return ret;
}