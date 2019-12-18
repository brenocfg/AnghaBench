#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct zsHpPriv {int /*<<< orphan*/  initFastChannelChangeControl; int /*<<< orphan*/  initRIFSSearchParams; int /*<<< orphan*/  initSearchStartDelay; int /*<<< orphan*/  initAgcControl; int /*<<< orphan*/  initAGC; int /*<<< orphan*/  initDesiredSigSize; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpDisableRifs(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    /* Disable RIFS function is to store these HW register initial value while the device plug-in and
       re-write to these register if the RIFS function is disabled  */

    // reg : 9850
    reg_write(0x9850, ((struct zsHpPriv*)wd->hpPrivate)->initDesiredSigSize);

    // reg : 985c
    reg_write(0x985c, ((struct zsHpPriv*)wd->hpPrivate)->initAGC);

    // reg : 9860
    reg_write(0x9800+(24<<2), ((struct zsHpPriv*)wd->hpPrivate)->initAgcControl);

    // reg : 9918
    reg_write(0x9800+(70<<2), ((struct zsHpPriv*)wd->hpPrivate)->initSearchStartDelay);

    // reg : 991c
    reg_write (0x99ec, ((struct zsHpPriv*)wd->hpPrivate)->initRIFSSearchParams);

    // reg : a388
    reg_write (0x9800+(738<<2), ((struct zsHpPriv*)wd->hpPrivate)->initFastChannelChangeControl);

    zfFlushDelayWrite(dev);

    return;
}