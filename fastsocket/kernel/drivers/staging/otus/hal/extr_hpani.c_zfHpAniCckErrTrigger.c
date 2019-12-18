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
struct zsHpPriv {int procPhyErr; struct zsAniState* curani; } ;
struct zsAniState {scalar_t__ noiseImmunityLevel; scalar_t__ rssiThrLow; scalar_t__ firstepLevel; } ;
typedef  scalar_t__ s32_t ;
struct TYPE_2__ {int frequency; scalar_t__ hpPrivate; } ;

/* Variables and functions */
 scalar_t__ BEACON_RSSI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZM_HAL_ANI_FIRSTEP_LEVEL ; 
 int /*<<< orphan*/  ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL ; 
 scalar_t__ ZM_HAL_FIRST_STEP_MAX ; 
 scalar_t__ ZM_HAL_NOISE_IMMUNE_MAX ; 
 int ZM_HAL_PROCESS_ANI ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpAniControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpAniCckErrTrigger(zdev_t* dev)
{
    struct zsAniState *aniState;
    s32_t rssi;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;

    //HALASSERT(chan != NULL);

    if ((HpPriv->procPhyErr & ZM_HAL_PROCESS_ANI) == 0)
        return;

    /* first, raise noise immunity level, up to max */
    aniState = HpPriv->curani;
    if (aniState->noiseImmunityLevel < ZM_HAL_NOISE_IMMUNE_MAX)
    {
        zfHpAniControl(dev, ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL,
                 aniState->noiseImmunityLevel + 1);
        return;
    }
    rssi = BEACON_RSSI(dev);
    if (rssi >  aniState->rssiThrLow)
    {
        /*
         * Beacon signal in mid and high range, raise firsteplevel.
         */
        if (aniState->firstepLevel < ZM_HAL_FIRST_STEP_MAX)
            zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, aniState->firstepLevel + 1);
    }
    else
    {
        /*
         * Beacon rssi is low, zero firstepLevel to maximize
         * CCK sensitivity.
         */
        if (wd->frequency < 3000)
        {
            if (aniState->firstepLevel > 0)
                zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, 0);
        }
    }
}