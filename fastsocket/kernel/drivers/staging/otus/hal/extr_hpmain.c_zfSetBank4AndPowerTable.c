#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u32_t ;
typedef  size_t u16_t ;
struct TYPE_7__ {size_t allowChannelCnt; size_t CurChIndex; TYPE_2__* allowChannel; } ;
struct TYPE_5__ {scalar_t__ DFSEnable; } ;
struct TYPE_8__ {TYPE_3__ regulationTable; TYPE_1__ sta; } ;
struct TYPE_6__ {int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (int,int) ; 
 scalar_t__ reverse_bits (int) ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwSleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfSetBank4AndPowerTable(zdev_t* dev, u32_t frequency, u8_t bw40,
        u8_t extOffset)
{
    u32_t chup = 1;
	u32_t bmode_LF_synth_freq = 0;
	u32_t amode_refsel_1 = 0;
	u32_t amode_refsel_0 = 1;
	u32_t addr2 = 1;
	u32_t addr1 = 0;
	u32_t addr0 = 0;

	u32_t d1;
	u32_t d0;
	u32_t tmp_0;
	u32_t tmp_1;
	u32_t data0;
	u32_t data1;

	u8_t chansel;
	u8_t chan_sel;
	u32_t temp_chan_sel;

    u16_t i;

    zmw_get_wlan_dev(dev);


    /* if enable 802.11h, need to record curent channel index in channel array */
    if (wd->sta.DFSEnable)
    {
        for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
        {
            if (wd->regulationTable.allowChannel[i].channel == frequency)
                break;
        }
        wd->regulationTable.CurChIndex = i;
    }

	if (bw40 == 1)
	{
        if (extOffset == 1)
        {
            frequency += 10;
        }
        else
        {
            frequency -= 10;
        }

	}


	if ( frequency > 3000 )
	{
	    if ( frequency % 10 )
	    {
	        /* 5M */
            chan_sel = (u8_t)((frequency - 4800)/5);
            chan_sel = (u8_t)(chan_sel & 0xff);
            chansel  = (u8_t)reverse_bits(chan_sel);
        }
        else
        {
            /* 10M : improve Tx EVM */
            chan_sel = (u8_t)((frequency - 4800)/10);
            chan_sel = (u8_t)(chan_sel & 0xff)<<1;
            chansel  = (u8_t)reverse_bits(chan_sel);

	        amode_refsel_1 = 1;
	        amode_refsel_0 = 0;
        }
	}
	else
	{
        //temp_chan_sel = (((frequency - 672)*2) - 3040)/10;
        if (frequency == 2484)
        {
   	        temp_chan_sel = 10 + (frequency - 2274)/5 ;
   	        bmode_LF_synth_freq = 1;
        }
        else
        {
            temp_chan_sel = 16 + (frequency - 2272)/5 ;
            bmode_LF_synth_freq = 0;
        }
        chan_sel = (u8_t)(temp_chan_sel << 2) & 0xff;
        chansel  = (u8_t)reverse_bits(chan_sel);
	}

	d1   = chansel;   //# 8 bits of chan
	d0   = addr0<<7 | addr1<<6 | addr2<<5
			| amode_refsel_0<<3 | amode_refsel_1<<2
			| bmode_LF_synth_freq<<1 | chup;

    tmp_0 = d0 & 0x1f;  //# 5-1
    tmp_1 = d1 & 0x1f;  //# 5-1
    data0 = tmp_1<<5 | tmp_0;

    tmp_0 = d0>>5 & 0x7;  //# 8-6
    tmp_1 = d1>>5 & 0x7;  //# 8-6
    data1 = tmp_1<<5 | tmp_0;

    /* Bank4 */
	reg_write (0x9800+(0x2c<<2), data0);
	reg_write (0x9800+(0x3a<<2), data1);
	//zm_debug_msg1("0x9800+(0x2c<<2 =  ", data0);
	//zm_debug_msg1("0x9800+(0x3a<<2 =  ", data1);


    zfFlushDelayWrite(dev);

    zfwSleep(dev, 10);

    return;
}