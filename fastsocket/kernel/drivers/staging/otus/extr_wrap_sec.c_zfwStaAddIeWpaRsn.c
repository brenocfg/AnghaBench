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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct usbdrv_private {scalar_t__* supIe; } ;

/* Variables and functions */
 int /*<<< orphan*/  copyToIntTxBuffer (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

u16_t zfwStaAddIeWpaRsn(zdev_t* dev, zbuf_t* buf, u16_t offset, u8_t frameType)
{
    struct usbdrv_private *macp = dev->ml_priv;
    //zm_msg1_mm(ZM_LV_0, "CWY - add wpaie content Length : ", macp->supIe[1]);
    if (macp->supIe[1] != 0)
    {
        copyToIntTxBuffer(dev, buf, macp->supIe, offset, macp->supIe[1]+2);
        //memcpy(buf->data[offset], macp->supIe, macp->supIe[1]+2);
        offset += (macp->supIe[1]+2);
    }

    return offset;
}