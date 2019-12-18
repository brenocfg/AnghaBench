#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_2__ zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* zfcbUsbOutComplete ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct usbdrv_private {TYPE_1__ usbCbFunctions; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfLnxPutUsbTxBuffer (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfLnxUsbSubmitTxData (TYPE_2__*) ; 

u32_t zfLnxUsbOut(zdev_t* dev, u8_t *hdr, u16_t hdrlen, u8_t *snap, u16_t snapLen,
        u8_t *tail, u16_t tailLen, zbuf_t *buf, u16_t offset)
{
    u32_t ret;
    struct usbdrv_private *macp = dev->ml_priv;

    /* Check length of tail buffer */
    //zm_assert((tailLen <= 16));

    /* Enqueue the packet into UsbTxBufQ */
    if (zfLnxPutUsbTxBuffer(dev, hdr, hdrlen, snap, snapLen, tail, tailLen, buf, offset) == 0xffff)
    {
        /* free packet */
        //printk("CWY - zfwPutUsbTxBuffer Error, free packet\n");
        //dev_kfree_skb_any(buf);
        macp->usbCbFunctions.zfcbUsbOutComplete(dev, buf, 0, hdr);
        return 0xffff;
    }

    //return 0;
    //printk("CWY - call zfwUsbSubmitTxData()\n");
    ret = zfLnxUsbSubmitTxData(dev);
    return ret;
}