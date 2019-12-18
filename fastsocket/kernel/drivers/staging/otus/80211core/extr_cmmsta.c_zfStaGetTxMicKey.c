#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
struct zsMicVar {int dummy; } ;
struct TYPE_3__ {scalar_t__ encryMode; scalar_t__ wpaState; struct zsMicVar txMicKey; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_STA_WPA_STATE_PK_OK ; 
 scalar_t__ ZM_TKIP ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

struct zsMicVar* zfStaGetTxMicKey(zdev_t* dev, zbuf_t* buf)
{
    zmw_get_wlan_dev(dev);

    /* if need not check MIC, return NULL */
    //if ( ((wd->sta.encryMode != ZM_TKIP)&&(wd->sta.encryMode != ZM_AES))||
    //     (wd->sta.wpaState < ZM_STA_WPA_STATE_PK_OK) )
    if ( (wd->sta.encryMode != ZM_TKIP) || (wd->sta.wpaState < ZM_STA_WPA_STATE_PK_OK) )
    {
        return NULL;
    }

    return (&wd->sta.txMicKey);
}