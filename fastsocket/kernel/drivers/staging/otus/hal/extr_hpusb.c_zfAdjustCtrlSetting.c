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
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {int halCapability; int hwFrequency; int* tPow2xCck; int* tPow2x2g; int tPow2x2g24HeavyClipOffset; int* tPow2x2gHt40; int* tPow2x2gHt20; int* tPow2x5g; int* tPow2x5gHt40; int* tPow2x5gHt20; scalar_t__ hwBw40; } ;
struct TYPE_3__ {scalar_t__ bScheduleScan; scalar_t__ bChannelScan; } ;
struct TYPE_4__ {int forceTxTPC; int maxTxPower2; int maxTxPower5; scalar_t__ wlanMode; scalar_t__ SignalStrength; TYPE_1__ sta; struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int ZM_HP_CAP_11N_ONE_TX_STREAM ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 int ZM_MIN_TPC ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_SIGNAL_THRESHOLD ; 
 int ZM_TPC_OFFSET ; 
 TYPE_2__* wd ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg2_tx (int /*<<< orphan*/ ,char*,int) ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfAdjustCtrlSetting(zdev_t* dev, u16_t* header, zbuf_t* buf)
{
    /* MIMO2 => OUTS FB-50 */
    /* length not change, only modify format */

    u32_t oldMT;
	u32_t oldMCS;

    u32_t phyCtrl;
    u32_t oldPhyCtrl;

    u16_t tpc = 0;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

   /* mm */
    if (header == NULL)
    {
        oldPhyCtrl = zmw_buf_readh(dev, buf, 4) | ((u32_t)zmw_buf_readh(dev, buf, 6) << 16);
    }
    else
    {
        oldPhyCtrl = header[2] | ((u32_t)header[3] <<16);
    }

	phyCtrl = 0;


	/* MT : Bit[1~0] */
	oldMT = oldPhyCtrl&0x3;
	phyCtrl |= oldMT;
    if ( oldMT == 0x3 )   /* DL-OFDM (Duplicate Legacy OFDM) */
		phyCtrl |= 0x1;


	/* PT : Bit[2]    HT PT: 0 Mixed mode    1 Green field */
	phyCtrl |= (oldPhyCtrl&0x4);

	/* Bandwidth control : Bit[4~3] */
	if ( oldPhyCtrl&0x800000 )    /* Bit23 : 40M */
	{
		#if 0
		if (oldMT == 0x3)             /* DL-OFDM */
            phyCtrl |= (0x3<<3);   /* 40M duplicate */
		else
			phyCtrl |= (0x2<<3);   /* 40M shared */
		#else
		if (oldMT == 0x2 && ((struct zsHpPriv*)wd->hpPrivate)->hwBw40)
		{
			phyCtrl |= (0x2<<3);   /* 40M shared */
		}
		#endif
	}
	else {
        oldPhyCtrl &= ~0x80000000;
    }

	/* MCS : Bit[24~18] */
	oldMCS = (oldPhyCtrl&0x7f0000)>>16;  /* Bit[22~16] */
	phyCtrl |= (oldMCS<<18);

	/* Short GI : Bit[31]*/
    phyCtrl |= (oldPhyCtrl&0x80000000);

	/* AM : Antenna mask */
	//if ((oldMT == 2) && (oldMCS > 7))
	if (hpPriv->halCapability & ZM_HP_CAP_11N_ONE_TX_STREAM)
	{
	    phyCtrl |= (0x1<<15);
	}
	else
	{
	    /* HT                     Tx 2 chain */
	    /* OFDM 6M/9M/12M/18M/24M Tx 2 chain */
	    /* OFDM 36M/48M/54M/      Tx 1 chain */
	    /* CCK                    Tx 2 chain */
	    if ((oldMT == 2) || (oldMT == 3))
	    {
	        phyCtrl |= (0x5<<15);
	    }
	    else if (oldMT == 1)
	    {
	        if ((oldMCS == 0xb) || (oldMCS == 0xf) ||
	            (oldMCS == 0xa) || (oldMCS == 0xe) ||
	            (oldMCS == 0x9))                       //6M/9M/12M/18M/24M
	        {
	            phyCtrl |= (0x5<<15);
	        }
	        else
	        {
	            phyCtrl |= (0x1<<15);
	        }
	    }
	    else //(oldMT==0)
	    {
	        phyCtrl |= (0x5<<15);
	    }
	}
	//else
	//    phyCtrl |= (0x1<<15);

	/* TPC */
	/* TODO : accelerating these code */
	if (hpPriv->hwFrequency < 3000)
	{
        if (oldMT == 0)
        {
            /* CCK */
            tpc = (hpPriv->tPow2xCck[oldMCS]&0x3f);
        }
        else if (oldMT == 1)
        {
            /* OFDM */
            if (oldMCS == 0xc)
            {
                tpc = (hpPriv->tPow2x2g[3]&0x3f);
            }
            else if (oldMCS == 0x8)
            {
                tpc = (hpPriv->tPow2x2g[2]&0x3f);
            }
            else if (oldMCS == 0xd)
            {
                tpc = (hpPriv->tPow2x2g[1]&0x3f);
            }
            else if (oldMCS == 0x9)
            {
                tpc = ((hpPriv->tPow2x2g[0]-hpPriv->tPow2x2g24HeavyClipOffset)&0x3f);
            }
            else
            {
                tpc = (hpPriv->tPow2x2g[0]&0x3f);
            }
        }
        else if (oldMT == 2)
        {
            if ( oldPhyCtrl&0x800000 )    /* Bit23 : 40M */
            {
                /* HT 40 */
                tpc = (hpPriv->tPow2x2gHt40[oldMCS&0x7]&0x3f);
            }
            else
            {
                /* HT 20 */
                tpc = (hpPriv->tPow2x2gHt20[oldMCS&0x7]&0x3f);
            }
        }
    }
    else  //5GHz
    {
        if (oldMT == 1)
        {
            /* OFDM */
            if (oldMCS == 0xc)
            {
                tpc = (hpPriv->tPow2x5g[3]&0x3f);
            }
            else if (oldMCS == 0x8)
            {
                tpc = (hpPriv->tPow2x5g[2]&0x3f);
            }
            else if (oldMCS == 0xd)
            {
                tpc = (hpPriv->tPow2x5g[1]&0x3f);
            }
            else
            {
                tpc = (hpPriv->tPow2x5g[0]&0x3f);
            }
        }
        else if (oldMT == 2)
        {
            if ( oldPhyCtrl&0x800000 )    /* Bit23 : 40M */
            {
                /* HT 40 */
                tpc = (hpPriv->tPow2x5gHt40[oldMCS&0x7]&0x3f);
            }
            else
            {
                /* HT 20 */
                tpc = (hpPriv->tPow2x5gHt20[oldMCS&0x7]&0x3f);
            }
        }
    }

    /* Tx power adjust for HT40 */
	/* HT40   +1dBm */
	if ((oldMT==2) && (oldPhyCtrl&0x800000) )
	{
	    tpc += 2;
	}
	tpc &= 0x3f;

    /* Evl force tx TPC */
    if(wd->forceTxTPC)
    {
        tpc = (u16_t)(wd->forceTxTPC & 0x3f);
    }

    if (hpPriv->hwFrequency < 3000) {
        wd->maxTxPower2 &= 0x3f;
        tpc = (tpc > wd->maxTxPower2)? wd->maxTxPower2 : tpc;
    } else {
        wd->maxTxPower5 &= 0x3f;
        tpc = (tpc > wd->maxTxPower5)? wd->maxTxPower5 : tpc;
    }


#define ZM_MIN_TPC     5
#define ZM_TPC_OFFSET  5
#define ZM_SIGNAL_THRESHOLD  56
    if ((wd->sta.bScheduleScan == FALSE) && (wd->sta.bChannelScan == FALSE))
    {
        if (( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
                && (zfStaIsConnected(dev))
                && (wd->SignalStrength > ZM_SIGNAL_THRESHOLD))
        {
            if (tpc > ((ZM_MIN_TPC+ZM_TPC_OFFSET)*2))
            {
                tpc -= (ZM_TPC_OFFSET*2);
            }
            else if (tpc > (ZM_MIN_TPC*2))
            {
                tpc = (ZM_MIN_TPC*2);
            }
        }
    }
#undef ZM_MIN_TPC
#undef ZM_TPC_OFFSET
#undef ZM_SIGNAL_THRESHOLD

    #ifndef ZM_OTUS_LINUX_PHASE_2
    phyCtrl |= (tpc & 0x3f) << 9;
    #endif

    /* Set bits[8:6]BF-MCS for heavy clip */
    if ((phyCtrl&0x3) == 2)
	{
	    phyCtrl |= ((phyCtrl >> 12) & 0x1c0);
    }

	/* PHY control */
    if (header == NULL)
    {
        zmw_buf_writeh(dev, buf, 4, (u16_t) (phyCtrl&0xffff));
        zmw_buf_writeh(dev, buf, 6, (u16_t) (phyCtrl>>16));
    }
    else
    {
        //PHY control L
        header[2] = (u16_t) (phyCtrl&0xffff);
        //PHY control H
        header[3] = (u16_t) (phyCtrl>>16);
    }

	zm_msg2_tx(ZM_LV_2, "old phy ctrl = ", oldPhyCtrl);
    zm_msg2_tx(ZM_LV_2, "new phy ctrl = ", phyCtrl);
	//DbgPrint("old phy ctrl =%08x \n", oldPhyCtrl);
    //DbgPrint("new phy ctrl =%08x \n", phyCtrl);
}