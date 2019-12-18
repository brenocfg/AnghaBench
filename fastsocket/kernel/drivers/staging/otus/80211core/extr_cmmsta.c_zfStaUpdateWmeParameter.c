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
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {scalar_t__ wmeConnected; scalar_t__ wmeParameterSetCount; int ac0PriorityHigherThanAc2; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 TYPE_2__* wd ; 
 int* zcCwTlb ; 
 int zfFindWifiElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfHpUpdateQosParameter (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 void* zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfStaUpdateWmeParameter(zdev_t* dev, zbuf_t* buf)
{
    u16_t   tmp;
    u16_t   aifs[5];
    u16_t   cwmin[5];
    u16_t   cwmax[5];
    u16_t   txop[5];
    u8_t    acm;
    u8_t    ac;
    u16_t   len;
    u16_t   i;
   	u16_t   offset;
    u8_t    rxWmeParameterSetCount;

    zmw_get_wlan_dev(dev);

    /* Update if WME parameter set count is changed */
    /* If connect to WME AP */
    if (wd->sta.wmeConnected != 0)
    {
        /* Find WME parameter element */
        if ((offset = zfFindWifiElement(dev, buf, 2, 1)) != 0xffff)
        {
            if ((len = zmw_rx_buf_readb(dev, buf, offset+1)) >= 7)
            {
                rxWmeParameterSetCount=zmw_rx_buf_readb(dev, buf, offset+8);
                if (rxWmeParameterSetCount != wd->sta.wmeParameterSetCount)
                {
                    zm_msg0_mm(ZM_LV_0, "wmeParameterSetCount changed!");
                    wd->sta.wmeParameterSetCount = rxWmeParameterSetCount;
                    /* retrieve WME parameter and update TxQ parameters */
                    acm = 0xf;
                    for (i=0; i<4; i++)
                    {
                        if (len >= (8+(i*4)+4))
                        {
                            tmp=zmw_rx_buf_readb(dev, buf, offset+10+i*4);
                            ac = (tmp >> 5) & 0x3;
                            if ((tmp & 0x10) == 0)
                            {
                                acm &= (~(1<<ac));
                            }
                            aifs[ac] = ((tmp & 0xf) * 9) + 10;
                            tmp=zmw_rx_buf_readb(dev, buf, offset+11+i*4);
                            /* Convert to 2^n */
                            cwmin[ac] = zcCwTlb[(tmp & 0xf)];
                            cwmax[ac] = zcCwTlb[(tmp >> 4)];
                            txop[ac]=zmw_rx_buf_readh(dev, buf,
                                    offset+12+i*4);
                        }
                    }

                    if ((acm & 0x4) != 0)
                    {
                        cwmin[2] = cwmin[0];
                        cwmax[2] = cwmax[0];
                        aifs[2] = aifs[0];
                        txop[2] = txop[0];
                    }
                    if ((acm & 0x8) != 0)
                    {
                        cwmin[3] = cwmin[2];
                        cwmax[3] = cwmax[2];
                        aifs[3] = aifs[2];
                        txop[3] = txop[2];
                    }
                    cwmin[4] = 3;
                    cwmax[4] = 7;
                    aifs[4] = 28;

                    if ((cwmin[2]+aifs[2]) > ((cwmin[0]+aifs[0])+1))
                    {
                        wd->sta.ac0PriorityHigherThanAc2 = 1;
                    }
                    else
                    {
                        wd->sta.ac0PriorityHigherThanAc2 = 0;
                    }
                    zfHpUpdateQosParameter(dev, cwmin, cwmax, aifs, txop);
                }
            }
        }
    } //if (wd->sta.wmeConnected != 0)
}