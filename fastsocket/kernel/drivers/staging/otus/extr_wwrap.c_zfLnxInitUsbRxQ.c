#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u16_t ;
struct usbdrv_private {int /*<<< orphan*/ ** UsbRxBufQ; int /*<<< orphan*/ * WlanRxDataUrb; scalar_t__ RxBufTail; scalar_t__ RxBufHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAX_RX_BUFFER_SIZE ; 
 int ZM_MAX_RX_URB_NUM ; 
 int /*<<< orphan*/ * dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfLnxPutUsbRxBuffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnxUsbIn (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zfLnxInitUsbRxQ(zdev_t* dev)
{
    u16_t i;
    zbuf_t *buf;
    struct usbdrv_private *macp = dev->ml_priv;

    /* Zero memory for UsbRxBufQ */
    memset(macp->UsbRxBufQ, 0, sizeof(zbuf_t *) * ZM_MAX_RX_URB_NUM);

    macp->RxBufHead = 0;

    for (i = 0; i < ZM_MAX_RX_URB_NUM; i++)
    {
        //buf = zfwBufAllocate(dev, ZM_MAX_RX_BUFFER_SIZE);
        buf = dev_alloc_skb(ZM_MAX_RX_BUFFER_SIZE);
        macp->UsbRxBufQ[i] = buf;
    }

    //macp->RxBufTail = ZM_MAX_RX_URB_NUM - 1;
    macp->RxBufTail = 0;

    /* Submit all Rx urbs */
    for (i = 0; i < ZM_MAX_RX_URB_NUM; i++)
    {
        zfLnxPutUsbRxBuffer(dev, macp->UsbRxBufQ[i]);
        zfLnxUsbIn(dev, macp->WlanRxDataUrb[i], macp->UsbRxBufQ[i]);
    }
}