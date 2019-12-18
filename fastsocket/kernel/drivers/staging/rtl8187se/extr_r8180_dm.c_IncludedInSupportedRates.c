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
typedef  size_t u8 ;
struct r8180_priv {TYPE_2__* ieee80211; } ;
struct TYPE_3__ {size_t rates_len; size_t rates_ex_len; size_t* rates; size_t* rates_ex; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */

int
IncludedInSupportedRates(
        struct r8180_priv       *priv,
        u8              TxRate  )
{
    u8 rate_len;
        u8 rate_ex_len;
        u8                      RateMask = 0x7F;
        u8                      idx;
        unsigned short          Found = 0;
        u8                      NaiveTxRate = TxRate&RateMask;

    rate_len = priv->ieee80211->current_network.rates_len;
        rate_ex_len = priv->ieee80211->current_network.rates_ex_len;
        for( idx=0; idx< rate_len; idx++ )
        {
                if( (priv->ieee80211->current_network.rates[idx] & RateMask) == NaiveTxRate )
                {
                        Found = 1;
                        goto found_rate;
                }
        }
    for( idx=0; idx< rate_ex_len; idx++ )
        {
                if( (priv->ieee80211->current_network.rates_ex[idx] & RateMask) == NaiveTxRate )
                {
                        Found = 1;
                        goto found_rate;
                }
        }
        return Found;
        found_rate:
        return Found;
}