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
struct zsAniState {scalar_t__ noiseImmunityLevel; scalar_t__ spurImmunityLevel; scalar_t__ rssiThrHigh; scalar_t__ firstepLevel; scalar_t__ rssiThrLow; scalar_t__ ofdmWeakSigDetectOff; } ;
typedef  scalar_t__ s32_t ;
struct TYPE_2__ {int frequency; scalar_t__ hpPrivate; } ;

/* Variables and functions */
 scalar_t__ BEACON_RSSI (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZM_HAL_ANI_FIRSTEP_LEVEL ; 
 int /*<<< orphan*/  ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL ; 
 int /*<<< orphan*/  ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION ; 
 int /*<<< orphan*/  ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL ; 
 scalar_t__ ZM_HAL_FIRST_STEP_MAX ; 
 scalar_t__ ZM_HAL_NOISE_IMMUNE_MAX ; 
 int ZM_HAL_PROCESS_ANI ; 
 scalar_t__ ZM_HAL_SPUR_IMMUNE_MAX ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpAniControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpAniOfdmErrTrigger(zdev_t* dev)
{
    struct zsAniState *aniState;
    s32_t rssi;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;

    //HALASSERT(chan != NULL);

    if ((HpPriv->procPhyErr & ZM_HAL_PROCESS_ANI) == 0)
        return;

    aniState = HpPriv->curani;
    /* First, raise noise immunity level, up to max */
    if (aniState->noiseImmunityLevel < ZM_HAL_NOISE_IMMUNE_MAX)
    {
        zfHpAniControl(dev, ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL, aniState->noiseImmunityLevel + 1);
        return;
    }
    /* then, raise spur immunity level, up to max */
    if (aniState->spurImmunityLevel < ZM_HAL_SPUR_IMMUNE_MAX)
    {
        zfHpAniControl(dev, ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL, aniState->spurImmunityLevel + 1);
        return;
    }
    rssi = BEACON_RSSI(dev);
    if (rssi > aniState->rssiThrHigh)
    {
        /*
         * Beacon rssi is high, can turn off ofdm weak sig detect.
         */
        if (!aniState->ofdmWeakSigDetectOff)
        {
            zfHpAniControl(dev, ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION, FALSE);
            zfHpAniControl(dev, ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL, 0);
            return;
        }
        /*
         * If weak sig detect is already off, as last resort, raise
         * first step level
         */
        if (aniState->firstepLevel < ZM_HAL_FIRST_STEP_MAX)
        {
            zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, aniState->firstepLevel + 1);
            return;
        }
    }
    else if (rssi > aniState->rssiThrLow)
    {
        /*
         * Beacon rssi in mid range, need ofdm weak signal detect,
         * but we can raise firststepLevel
         */
        if (aniState->ofdmWeakSigDetectOff)
            zfHpAniControl(dev, ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION, TRUE);
        if (aniState->firstepLevel < ZM_HAL_FIRST_STEP_MAX)
            zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, aniState->firstepLevel + 1);
        return;
    }
    else
    {
        /*
         * Beacon rssi is low, if in 11b/g mode, turn off ofdm
         * weak sign detction and zero firstepLevel to maximize
         * CCK sensitivity
         */
        if (wd->frequency < 3000)
        {
            if (!aniState->ofdmWeakSigDetectOff)
                zfHpAniControl(dev, ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION, FALSE);
            if (aniState->firstepLevel > 0)
                zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, 0);
            return;
        }
    }
}