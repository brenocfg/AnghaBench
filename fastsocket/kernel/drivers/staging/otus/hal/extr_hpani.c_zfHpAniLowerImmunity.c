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
struct zsHpPriv {struct zsAniState* curani; } ;
struct zsAniState {scalar_t__ rssiThrHigh; scalar_t__ rssiThrLow; scalar_t__ firstepLevel; scalar_t__ spurImmunityLevel; scalar_t__ noiseImmunityLevel; scalar_t__ ofdmWeakSigDetectOff; } ;
typedef  scalar_t__ s32_t ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 scalar_t__ BEACON_RSSI (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZM_HAL_ANI_FIRSTEP_LEVEL ; 
 int /*<<< orphan*/  ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL ; 
 int /*<<< orphan*/  ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION ; 
 int /*<<< orphan*/  ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpAniControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpAniLowerImmunity(zdev_t* dev)
{
    struct zsAniState *aniState;
    s32_t rssi;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;
    aniState = HpPriv->curani;

    rssi = BEACON_RSSI(dev);
    if (rssi > aniState->rssiThrHigh)
    {
        /*
         * Beacon signal is high, leave ofdm weak signal detection off
         * or it may oscillate. Let it fall through.
         */
    }
    else if (rssi > aniState->rssiThrLow)
    {
        /*
         * Beacon rssi in mid range, turn on ofdm weak signal
         * detection or lower first step level.
         */
        if (aniState->ofdmWeakSigDetectOff)
        {
            zfHpAniControl(dev, ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION, TRUE);
            return;
        }
        if (aniState->firstepLevel > 0)
        {
            zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, aniState->firstepLevel - 1);
            return;
        }
    }
    else
    {
        /*
         * Beacon rssi is low, reduce first step level.
         */
        if (aniState->firstepLevel > 0)
        {
            zfHpAniControl(dev, ZM_HAL_ANI_FIRSTEP_LEVEL, aniState->firstepLevel - 1);
            return;
        }
    }
    /* then lower spur immunity level, down to zero */
    if (aniState->spurImmunityLevel > 0)
    {
        zfHpAniControl(dev, ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL, aniState->spurImmunityLevel - 1);
        return;
    }
    /*
     * if all else fails, lower noise immunity level down to a min value
     * zero for now
     */
    if (aniState->noiseImmunityLevel > 0)
    {
        zfHpAniControl(dev, ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL, aniState->noiseImmunityLevel - 1);
        return;
    }
}