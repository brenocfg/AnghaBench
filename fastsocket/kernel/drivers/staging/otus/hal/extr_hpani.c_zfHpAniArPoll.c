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
typedef  scalar_t__ u32_t ;
struct TYPE_3__ {int /*<<< orphan*/  ast_ani_cckerrs; int /*<<< orphan*/  ast_ani_ofdmerrs; } ;
struct zsHpPriv {int procPhyErr; int aniPeriod; TYPE_1__ stats; scalar_t__ hasHwPhyCounters; struct zsAniState* curani; } ;
struct zsAniState {int listenTime; int ofdmPhyErrCount; int cckPhyErrCount; int ofdmTrigLow; int cckTrigLow; int ofdmTrigHigh; int cckTrigHigh; } ;
struct TYPE_4__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int ZM_HAL_PROCESS_ANI ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpAniCckErrTrigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpAniLowerImmunity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpAniOfdmErrTrigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpAniRestart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpAniArPoll(zdev_t* dev, u32_t listenTime, u32_t phyCnt1, u32_t phyCnt2)
{
    struct zsAniState *aniState;
    //s32_t listenTime;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;

    /*
     * Since we're called from end of rx tasklet, we also check for
     * AR processing now
     */

    aniState = HpPriv->curani;
    //HpPriv->stats.ast_nodestats = *stats;       /* XXX optimize? */

    //listenTime = zfHpAniGetListenTime(dev);
    //if (listenTime < 0)
    //{
    //    HpPriv->stats.ast_ani_lneg++;
    //    /* restart ANI period if listenTime is invalid */
    //    zfHpAniRestart(dev);
    //    return;
    //}
    /* XXX beware of overflow? */
    aniState->listenTime += listenTime;

    if (HpPriv->hasHwPhyCounters)
    {
        //u32_t phyCnt1, phyCnt2;
        u32_t ofdmPhyErrCnt, cckPhyErrCnt;

        /* NB: these are not reset-on-read */
        //phyCnt1 = 0;//OS_REG_READ(ah, AR_PHY_ERR_1);
        //phyCnt2 = 0;//OS_REG_READ(ah, AR_PHY_ERR_2);
        /* XXX sometimes zero, why? */
        //if (phyCnt1 < aniState->ofdmPhyErrBase ||
        //    phyCnt2 < aniState->cckPhyErrBase)
        //{
        //    if (phyCnt1 < aniState->ofdmPhyErrBase)
        //    {
        //        zm_debug_msg2("phyCnt1 = 0x", phyCnt1);
        //        zm_debug_msg2("resetting counter value to 0x", aniState->ofdmPhyErrBase);
        //        //OS_REG_WRITE(ah, AR_PHY_ERR_1, aniState->ofdmPhyErrBase);
        //        //OS_REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
        //    }
        //    if (phyCnt2 < aniState->cckPhyErrBase)
        //    {
        //        zm_debug_msg2("phyCnt2 = 0x", phyCnt2);
        //        zm_debug_msg2("resetting counter value to 0x", aniState->cckPhyErrBase);
        //        //OS_REG_WRITE(ah, AR_PHY_ERR_2, aniState->cckPhyErrBase);
        //        //OS_REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);
        //    }
        //    return;     /* XXX */
        //}
        /* NB: only use ast_ani_*errs with AH_PRIVATE_DIAG */
        //ofdmPhyErrCnt = phyCnt1 - aniState->ofdmPhyErrBase;
        //HpPriv->stats.ast_ani_ofdmerrs += ofdmPhyErrCnt - aniState->ofdmPhyErrCount;
        //aniState->ofdmPhyErrCount = ofdmPhyErrCnt;
        ofdmPhyErrCnt = phyCnt1;
        HpPriv->stats.ast_ani_ofdmerrs += ofdmPhyErrCnt;
        aniState->ofdmPhyErrCount += ofdmPhyErrCnt;

        //cckPhyErrCnt = phyCnt2 - aniState->cckPhyErrBase;
        //HpPriv->stats.ast_ani_cckerrs += cckPhyErrCnt - aniState->cckPhyErrCount;
        //aniState->cckPhyErrCount = cckPhyErrCnt;
        cckPhyErrCnt = phyCnt2;
        HpPriv->stats.ast_ani_cckerrs += cckPhyErrCnt;
        aniState->cckPhyErrCount += cckPhyErrCnt;
    }
    /*
     * If ani is not enabled, return after we've collected
     * statistics
     */
    if ((HpPriv->procPhyErr & ZM_HAL_PROCESS_ANI) == 0)
        return;
    if (aniState->listenTime > 5 * HpPriv->aniPeriod)
    {
        /*
         * Check to see if need to lower immunity if
         * 5 aniPeriods have passed
         */
        if (aniState->ofdmPhyErrCount <= aniState->listenTime *
             aniState->ofdmTrigLow/1000 &&
            aniState->cckPhyErrCount <= aniState->listenTime *
             aniState->cckTrigLow/1000)
            zfHpAniLowerImmunity(dev);
        zfHpAniRestart(dev);
    }
    else if (aniState->listenTime > HpPriv->aniPeriod)
    {
        /* check to see if need to raise immunity */
        if (aniState->ofdmPhyErrCount > aniState->listenTime *
            aniState->ofdmTrigHigh / 1000)
        {
            zfHpAniOfdmErrTrigger(dev);
            zfHpAniRestart(dev);
        }
        else if (aniState->cckPhyErrCount > aniState->listenTime *
               aniState->cckTrigHigh / 1000)
        {
            zfHpAniCckErrTrigger(dev);
            zfHpAniRestart(dev);
        }
    }
}