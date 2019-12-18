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
struct zsHpPriv {int isSiteSurvey; int* eepromImage; scalar_t__ hwFrequency; int currentAckRtsTpc; scalar_t__ strongRSSI; scalar_t__ rxStrongRSSI; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 scalar_t__ ZM_CH_G_14 ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpBeginSiteSurvey(zdev_t* dev, u8_t status)
{
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    if ( status == 1 )
    { // Connected
        hpPriv->isSiteSurvey = 1;
    }
    else
    { // Not connected
        hpPriv->isSiteSurvey = 0;
    }

    /* reset workaround state to default */
//    if (hpPriv->rxStrongRSSI == 1)
    {
        hpPriv->rxStrongRSSI = 0;
        if ((hpPriv->eepromImage[0x100+0x110*2/4]&0xff) == 0x80) //FEM TYPE
        {
            if (hpPriv->hwFrequency <= ZM_CH_G_14)
            {
                zfDelayWriteInternalReg(dev, 0x1c8960, 0x9b49);
            }
            else
            {
                zfDelayWriteInternalReg(dev, 0x1c8960, 0x0900);
            }
        }
        else
        {
            zfDelayWriteInternalReg(dev, 0x1c8960, 0x9b40);
        }
        zfFlushDelayWrite(dev);
    }
//    if (hpPriv->strongRSSI == 1)
    {
        hpPriv->strongRSSI = 0;
        zfDelayWriteInternalReg(dev, 0x1c3694, ((hpPriv->currentAckRtsTpc&0x3f) << 20) | (0x5<<26));
        zfDelayWriteInternalReg(dev, 0x1c3bb4, ((hpPriv->currentAckRtsTpc&0x3f) << 5 ) | (0x5<<11) |
                                               ((hpPriv->currentAckRtsTpc&0x3f) << 21) | (0x5<<27)  );
        zfFlushDelayWrite(dev);
    }
}