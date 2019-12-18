#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
struct usbdrv_private {int /*<<< orphan*/  ioctl_sem; int /*<<< orphan*/  kevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_MUTEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent ; 

u8_t zfLnxCreateThread(zdev_t *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;

    /* Create Mutex and keventd */
    INIT_WORK(&macp->kevent, kevent);
    init_MUTEX(&macp->ioctl_sem);

    return 0;
}