#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
struct zsHpPriv {int /*<<< orphan*/ * eepromImage; } ;
struct ar5416Eeprom {int dummy; } ;
struct TYPE_5__ {struct zsHpPriv* hpPrivate; } ;
struct TYPE_4__ {scalar_t__ bChannel; size_t tPower; scalar_t__ flag; } ;
typedef  TYPE_1__ CAL_CTL_EDGES ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 size_t AR5416_MAX_RATE_POWER ; 
 size_t AR5416_NUM_BAND_EDGES ; 
 scalar_t__ ZM_CH_G_14 ; 
 scalar_t__ fbin2freq (scalar_t__,size_t) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zm_dbg (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfGetMaxEdgePower(zdev_t* dev, CAL_CTL_EDGES *pCtlEdges, u32_t freq)
{
    u8_t i;
    u8_t maxEdgePower;
    u8_t is2GHz;
    struct zsHpPriv* hpPriv;
    struct ar5416Eeprom* eepromImage;

    zmw_get_wlan_dev(dev);

    hpPriv = wd->hpPrivate;

    eepromImage = (struct ar5416Eeprom*)&(hpPriv->eepromImage[(1024+512)/4]);

    if(freq > ZM_CH_G_14)
        is2GHz = 0;
    else
        is2GHz = 1;

    maxEdgePower = AR5416_MAX_RATE_POWER;

    /* Get the edge power */
    for (i = 0; (i < AR5416_NUM_BAND_EDGES) && (pCtlEdges[i].bChannel != AR5416_BCHAN_UNUSED) ; i++)
    {
        /*
         * If there's an exact channel match or an inband flag set
         * on the lower channel use the given rdEdgePower
         */
        if (freq == fbin2freq(pCtlEdges[i].bChannel, is2GHz))
        {
            maxEdgePower = pCtlEdges[i].tPower;
            #ifdef ZM_ENABLE_BANDEDGES_WINDOWS_DEBUG
            zm_dbg(("zfGetMaxEdgePower index i = %d \n", i));
            #endif
            break;
        }
        else if ((i > 0) && (freq < fbin2freq(pCtlEdges[i].bChannel, is2GHz)))
        {
            if (fbin2freq(pCtlEdges[i - 1].bChannel, is2GHz) < freq && pCtlEdges[i - 1].flag)
            {
                maxEdgePower = pCtlEdges[i - 1].tPower;
                #ifdef ZM_ENABLE_BANDEDGES_WINDOWS_DEBUG
                zm_dbg(("zfGetMaxEdgePower index i-1 = %d \n", i-1));
                #endif
            }
            /* Leave loop - no more affecting edges possible in this monotonic increasing list */
            break;
        }

    }

    if( i == AR5416_NUM_BAND_EDGES )
    {
        if (freq > fbin2freq(pCtlEdges[i - 1].bChannel, is2GHz) && pCtlEdges[i - 1].flag)
        {
            maxEdgePower = pCtlEdges[i - 1].tPower;
            #ifdef ZM_ENABLE_BANDEDGES_WINDOWS_DEBUG
            zm_dbg(("zfGetMaxEdgePower index=>i-1 = %d \n", i-1));
            #endif
        }
    }

    zm_assert(maxEdgePower > 0);

  #ifdef ZM_ENABLE_BANDEDGES_WINDOWS_DEBUG
    if ( maxEdgePower == AR5416_MAX_RATE_POWER )
    {
        zm_dbg(("zfGetMaxEdgePower = %d !!!\n", AR5416_MAX_RATE_POWER));
    }
  #endif
    return maxEdgePower;
}