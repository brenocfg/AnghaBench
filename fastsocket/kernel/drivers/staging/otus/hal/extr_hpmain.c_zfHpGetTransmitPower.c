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
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {int hwFrequency; int* tPow2x2g; int* tPow2x5g; } ;
struct TYPE_2__ {int maxTxPower2; int maxTxPower5; struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfHpGetTransmitPower(zdev_t* dev)
{
    struct zsHpPriv*    hpPriv;
    u16_t               tpc     = 0;

    zmw_get_wlan_dev(dev);
    hpPriv  = wd->hpPrivate;

    if (hpPriv->hwFrequency < 3000) {
        tpc = hpPriv->tPow2x2g[0] & 0x3f;
        wd->maxTxPower2 &= 0x3f;
        tpc = (tpc > wd->maxTxPower2)? wd->maxTxPower2 : tpc;
    } else {
        tpc = hpPriv->tPow2x5g[0] & 0x3f;
        wd->maxTxPower5 &= 0x3f;
        tpc = (tpc > wd->maxTxPower5)? wd->maxTxPower5 : tpc;
    }

    return tpc;
}