#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;

/* Variables and functions */
 scalar_t__* zcOfdmPhyCrtlToRate ; 

u8_t zfPhyCtrlToRate(u32_t phyCtrl)
{
    u32_t mt, mcs, sg;
    u8_t rate = 0;

    mt = phyCtrl & 0x3;
    mcs = (phyCtrl>>18) & 0x3f;
    sg = (phyCtrl>>31) & 0x1;

    if ((mt == 0) && (mcs <=3))
    {
        rate = (u8_t)mcs;
    }
    else if ((mt == 1) && (mcs >= 0x8) && (mcs <= 0xf))
    {
        rate = zcOfdmPhyCrtlToRate[mcs-8];
    }
    else if ((mt == 2) && (mcs <= 15))
    {
        rate = (u8_t)mcs + 12;
        if(sg) {
            if (mcs != 7)
            {
                rate = (u8_t)mcs + 12 + 2;
            }
            else //MCS7-SG
            {
                rate = (u8_t)30;
            }
        }
    }

    return rate;
}