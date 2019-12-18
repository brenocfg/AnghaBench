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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int ZM_CH_G_1 ; 
 int ZM_CH_G_14 ; 

u16_t zfChNumToFreq(zdev_t* dev, u8_t ch, u8_t freqBand)
{
    u16_t freq = 0xffff;

    if ( freqBand == 0 )
    {
        if (ch > 14)
        {   /* adapter is at 5 GHz band */
            freqBand = 2;
        }
        else
        {
            freqBand = 1;
        }
    }

    if ( freqBand == 2 )
    {   /* the channel belongs to 5 GHz band */
        if ( (ch >= 184)&&(ch <= 196) )
        {
            freq = 4000 + ch*5;
        }
        else
        {
            freq = 5000 + ch*5;
        }
    }
    else
    {   /* the channel belongs to 2.4 GHz band */
        if ( ch == 14 )
        {
            freq = ZM_CH_G_14;
        }
        else
        {
            freq = ZM_CH_G_1 + (ch-1)*5;
        }
    }

    return freq;
}