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
struct TYPE_3__ {int /*<<< orphan*/  ast_ani_lzero; } ;
struct zsHpPriv {TYPE_1__ stats; struct zsAniState* curani; } ;
struct zsAniState {scalar_t__ cycleCount; scalar_t__ rxFrameCount; scalar_t__ txFrameCount; } ;
typedef  int s32_t ;
struct TYPE_4__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int CLOCK_RATE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

s32_t zfHpAniGetListenTime(zdev_t* dev)
{
    struct zsAniState *aniState;
    u32_t txFrameCount, rxFrameCount, cycleCount;
    s32_t listenTime;
    struct zsHpPriv *HpPriv;

    zmw_get_wlan_dev(dev);
    HpPriv = (struct zsHpPriv*)wd->hpPrivate;

    txFrameCount = 0;//OS_REG_READ(ah, AR_TFCNT);
    rxFrameCount = 0;//OS_REG_READ(ah, AR_RFCNT);
    cycleCount = 0;//OS_REG_READ(ah, AR_CCCNT);

    aniState = HpPriv->curani;
    if (aniState->cycleCount == 0 || aniState->cycleCount > cycleCount)
    {
        /*
         * Cycle counter wrap (or initial call); it's not possible
         * to accurately calculate a value because the registers
         * right shift rather than wrap--so punt and return 0.
         */
        listenTime = 0;
        HpPriv->stats.ast_ani_lzero++;
    }
    else
    {
        s32_t ccdelta = cycleCount - aniState->cycleCount;
        s32_t rfdelta = rxFrameCount - aniState->rxFrameCount;
        s32_t tfdelta = txFrameCount - aniState->txFrameCount;
        listenTime = (ccdelta - rfdelta - tfdelta) / CLOCK_RATE;
    }
    aniState->cycleCount = cycleCount;
    aniState->txFrameCount = txFrameCount;
    aniState->rxFrameCount = rxFrameCount;
    return listenTime;
}