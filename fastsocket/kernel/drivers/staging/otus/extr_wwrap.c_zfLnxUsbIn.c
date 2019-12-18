#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zbuf_t ;
typedef  int /*<<< orphan*/  urb_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct usbdrv_private {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_WLAN_RX_PIPE ; 
 int /*<<< orphan*/  ZM_MAX_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  zfLnxUsbDataIn_callback ; 
 int /*<<< orphan*/  zfLnxUsbSubmitBulkUrb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

u32_t zfLnxUsbIn(zdev_t* dev, urb_t *urb, zbuf_t *buf)
{
    u32_t ret;
    struct usbdrv_private *macp = dev->ml_priv;

    /* Submit a rx urb */
    ret = zfLnxUsbSubmitBulkUrb(urb, macp->udev, USB_WLAN_RX_PIPE,
            USB_DIR_IN, buf->data, ZM_MAX_RX_BUFFER_SIZE,
            zfLnxUsbDataIn_callback, dev);
    //CWYang(-)
    //if (ret != 0)
    //    printk("zfwUsbSubmitBulkUrb fail, status: 0x%08x\n", (int)ret);

    return ret;
}