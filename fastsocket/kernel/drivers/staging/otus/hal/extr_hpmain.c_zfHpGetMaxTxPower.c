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
typedef  int u8_t ;
struct zsHpPriv {int hwFrequency; int* tPow2xCck; int* tPow2x5g; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfHpGetMaxTxPower(zdev_t* dev)
{
    struct zsHpPriv*    hpPriv;
    u8_t               tpc     = 0;

    zmw_get_wlan_dev(dev);
    hpPriv  = wd->hpPrivate;

    if (hpPriv->hwFrequency < 3000)
    {
        tpc = (hpPriv->tPow2xCck[0]&0x3f);
    }
    else
    {
        tpc =(hpPriv->tPow2x5g[0]&0x3f);
    }

    return tpc;
}