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
struct zsHpPriv {scalar_t__ hasHwPhyCounters; struct zsAniState* curani; } ;
struct zsAniState {scalar_t__ cckPhyErrCount; scalar_t__ ofdmPhyErrCount; scalar_t__ cckPhyErrBase; scalar_t__ ofdmPhyErrBase; scalar_t__ listenTime; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpAniRestart(zdev_t* dev)
{
    struct zsAniState *aniState;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;
    aniState = HpPriv->curani;

    aniState->listenTime = 0;
    if (HpPriv->hasHwPhyCounters)
    {
        //if (aniState->ofdmTrigHigh > AR_PHY_COUNTMAX)
        //{
        //    aniState->ofdmPhyErrBase = 0;
        //    zm_debug_msg0("OFDM Trigger is too high for hw counters");
        //}
        //else
        //    aniState->ofdmPhyErrBase = AR_PHY_COUNTMAX - aniState->ofdmTrigHigh;
        //if (aniState->cckTrigHigh > AR_PHY_COUNTMAX)
        //{
        //    aniState->cckPhyErrBase = 0;
        //    zm_debug_msg0("CCK Trigger is too high for hw counters");
        //}
        //else
        //    aniState->cckPhyErrBase = AR_PHY_COUNTMAX - aniState->cckTrigHigh;
        //zm_debug_msg2("Writing ofdmbase = 0x", aniState->ofdmPhyErrBase);
        //zm_debug_msg2("Writing cckbase = 0x", aniState->cckPhyErrBase);
        //OS_REG_WRITE(ah, AR_PHY_ERR_1, aniState->ofdmPhyErrBase);
        //OS_REG_WRITE(ah, AR_PHY_ERR_2, aniState->cckPhyErrBase);
        //OS_REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
        //OS_REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);
        aniState->ofdmPhyErrBase = 0;
        aniState->cckPhyErrBase = 0;
    }
    aniState->ofdmPhyErrCount = 0;
    aniState->cckPhyErrCount = 0;
}