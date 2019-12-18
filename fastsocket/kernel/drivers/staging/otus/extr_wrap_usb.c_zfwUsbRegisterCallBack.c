#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_2__ zdev_t ;
struct zfCbUsbFuncTbl {int /*<<< orphan*/  zfcbUsbOutComplete; int /*<<< orphan*/  zfcbUsbRegIn; int /*<<< orphan*/  zfcbUsbRecv; } ;
struct TYPE_4__ {int /*<<< orphan*/  zfcbUsbOutComplete; int /*<<< orphan*/  zfcbUsbRegIn; int /*<<< orphan*/  zfcbUsbRecv; } ;
struct usbdrv_private {TYPE_1__ usbCbFunctions; } ;

/* Variables and functions */

void zfwUsbRegisterCallBack(zdev_t* dev, struct zfCbUsbFuncTbl *zfUsbFunc) {
    struct usbdrv_private *macp = dev->ml_priv;

    macp->usbCbFunctions.zfcbUsbRecv = zfUsbFunc->zfcbUsbRecv;
    macp->usbCbFunctions.zfcbUsbRegIn = zfUsbFunc->zfcbUsbRegIn;
    macp->usbCbFunctions.zfcbUsbOutComplete = zfUsbFunc->zfcbUsbOutComplete;

    return;
}