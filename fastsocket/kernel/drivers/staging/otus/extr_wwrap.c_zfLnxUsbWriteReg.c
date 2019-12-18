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
typedef  int u16_t ;
struct usbdrv_private {int /*<<< orphan*/  regUsbWriteBuf; int /*<<< orphan*/  udev; int /*<<< orphan*/  RegOutUrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  USB_REG_OUT_PIPE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfLnxUsbRegOut_callback ; 
 int /*<<< orphan*/  zfLnxUsbSubmitIntUrb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

u32_t zfLnxUsbWriteReg(zdev_t* dev, u32_t* cmd, u16_t cmdLen)
{
    struct usbdrv_private *macp = dev->ml_priv;
    u32_t ret;

#ifdef ZM_CONFIG_BIG_ENDIAN
    int ii = 0;

    for(ii=0; ii<(cmdLen>>2); ii++)
	cmd[ii] = cpu_to_le32(cmd[ii]);
#endif

    memcpy(macp->regUsbWriteBuf, cmd, cmdLen);

    /* Issue an USB Out transfer */
    /* Submit a tx urb */
    ret = zfLnxUsbSubmitIntUrb(macp->RegOutUrb, macp->udev,
            USB_REG_OUT_PIPE, USB_DIR_OUT, macp->regUsbWriteBuf,
            cmdLen, zfLnxUsbRegOut_callback, dev, 1);

    return ret;
}