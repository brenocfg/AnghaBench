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
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int ZM_CH_G_1 ; 
 int ZM_CH_G_14 ; 

u8_t zfChFreqToNum(u16_t freq, u8_t* pbIs5GBand)
{
    u8_t   ch;
    u8_t   Is5GBand;

    /* to avoid NULL value */
    if ( pbIs5GBand == NULL )
    {
        pbIs5GBand = &Is5GBand;
    }

    *pbIs5GBand = FALSE;

    if ( freq == ZM_CH_G_14 )
    {
        ch = 14;
    }
    else if ( freq < 4000 )
    {
        ch = (freq - ZM_CH_G_1) / 5 + 1;
    }
    else if ( freq < 5000 )
    {
        ch = (freq - 4000) / 5;
        *pbIs5GBand = TRUE;
    }
    else
    {
        ch = (freq - 5000) / 5;
        *pbIs5GBand = TRUE;
    }

    return ch;
}